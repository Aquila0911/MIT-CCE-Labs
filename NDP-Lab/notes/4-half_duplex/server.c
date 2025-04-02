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
    char buffer[1024]; // Buffer to send and receive

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

    // Accept connection
    newsock = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&client_len); // Use diff struct for client

    struct sockaddr_in client_info;
    socklen_t client_info_len = sizeof(client_info);
    getpeername(newsock, (struct sockaddr*)&client_info, &client_info_len);
    printf("Client is connected from IP: %s, Port: %d\n\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    while(1) {
        // Receive message
        memset(buffer, 0, sizeof(buffer));
        recv(newsock, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit") == 0) break;
        printf("Client: %s\n", buffer);

        // Send message
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(newsock, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "exit") == 0) break;
    }

    // Close sockets
    close(newsock);
    close(sockfd);
    printf("Server socket closed. Shutting down...\n");

    return 0;
}
