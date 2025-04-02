#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 3300
#define SERVER_IP "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024]; // Buffer to send and receive

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    // Connect to server
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Connected to server!\n\n");

    while(1) {
        // Send message
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        send(sockfd, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "exit") == 0) break;

        // Receive message
        memset(buffer, 0, sizeof(buffer));
        char buffer[1024] = {0};
        recv(sockfd, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
    }

    // Close socket
    close(sockfd);
    printf("Disconnected from server...\n");

    return 0;
}
