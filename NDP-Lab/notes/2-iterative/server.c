#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3300

int main() {
    int sockfd, newsock;
    struct sockaddr_in address, client_addr;
    socklen_t addrlen = sizeof(address), client_len = sizeof(client_addr);

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

    // getsockname(): gets IP and Port of current (server) socket
    struct sockaddr_in server_info;
    socklen_t server_info_len = sizeof(server_info);
    getsockname(sockfd, (struct sockaddr*)&server_info, &server_info_len);
    printf("Server is running on IP: %s, Port: %d\n\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    // Infinite loop for ITERATIVE handling of clients
    while (1) {
        printf("Waiting for a client to connect...\n");

        // Accept connection
        newsock = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&client_len);
        if (newsock < 0) {
            perror("Accept failed");
            continue; // Skip and wait for the next client
        }

        // getpeername(): gets IP and Port of peer (client) socket
        struct sockaddr_in client_info;
        socklen_t client_info_len = sizeof(client_info);
        getpeername(newsock, (struct sockaddr*)&client_info, &client_info_len);
        printf("Client connected from IP: %s, Port: %d\n\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // Receive message
        char buffer[1024] = {0};
        recv(newsock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            printf("Shutdown command received. Server closing.\n");
            close(newsock);
            close(sockfd);
            break;  // Exit loop and close server socket
        }

        // Send message
        char msg[1024];
        printf("Enter message to send: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0; // Remove newline
        send(newsock, msg, strlen(msg), 0);
        printf("Message sent to client!\n\n");

        // Close client socket
        close(newsock);
        printf("Client connection closed.\n\n");
    }

    // Close server socket (will never reach here unless manually terminated)
    close(sockfd);
    printf("Server socket closed. Shutting down...\n");

    return 0;
}
