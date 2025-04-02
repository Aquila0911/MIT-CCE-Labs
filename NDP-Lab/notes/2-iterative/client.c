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

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }
    printf("Connected to server at %s:%d\n", SERVER_IP, PORT);

    // Send message
    char msg[1024]; // Input
    printf("Enter message to send: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;
    send(sockfd, msg, strlen(msg), 0);
    printf("Message sent to server! Awaiting response...\n\n");

    // Receive message
    char buffer[1024] = {0};
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server: %s\n\n", buffer);

    // Close socket
    close(sockfd);
    printf("Disconnected from server...\n");

    return 0;
}
