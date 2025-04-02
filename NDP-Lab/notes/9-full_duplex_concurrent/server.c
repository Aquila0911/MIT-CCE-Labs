#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3300

int main() {
    int sockfd, newsock;
    struct sockaddr_in address, client_addr;
    socklen_t addrlen = sizeof(address), client_len = sizeof(client_addr);
    char buffer[1024];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket to specific address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&address, sizeof(address));

    // Listen for connections
    listen(sockfd, 3);

    struct sockaddr_in server_info;
    socklen_t server_info_len = sizeof(server_info);
    getsockname(sockfd, (struct sockaddr*)&server_info, &server_info_len);
    printf("Server is running on IP: %s, Port: %d\n\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    while (1) {
        // Accept connection
        newsock = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&client_len);

        struct sockaddr_in client_info;
        socklen_t client_info_len = sizeof(client_info);
        getpeername(newsock, (struct sockaddr*)&client_info, &client_info_len);
        printf("Client is connected from IP: %s, Port: %d\n\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // 1st Child process to handle client (concurrent)
        if (fork() == 0) { 
            close(sockfd);

            // 2nd Child for receiving (full duplex)
            if (fork() == 0) { 
                char buffer[1024];
                while (1) {
                    memset(buffer, 0, sizeof(buffer));
                    int bytes_received = recv(newsock, buffer, sizeof(buffer), 0);
                
                    if (bytes_received <= 0) {
                        printf("Client disconnected.\n");
                    break;
                    }
                    if (strcmp(buffer, "exit") == 0) { // Check if client sent "exit"
                        printf("Client sent exit command. Closing connection.\n");
                        break;
                    }
                    printf("--Client:\n%s\n", buffer);
                }

                close(newsock);
                exit(0); // Exit child 2
            }

            // 2nd Parent for sending (full duplex)
            char msg[1024];
            while (1) {
                printf("--You:\n");
                fgets(msg, sizeof(msg), stdin);
                msg[strcspn(msg, "\n")] = 0;
                send(newsock, msg, strlen(msg), 0);
                if (strcmp(msg, "exit") == 0) break;
            }

            close(newsock);
            exit(0); // Exit child 1
        }
        // 1st Parent to listen for new clients (concurrent)
        close(newsock); // Parent 1 closes newsock
    }

    // Close socket
    close(sockfd);
    printf("Server socket closed. Shutting down...\n");

    return 0;
}
