#include <stdio.h>
#include <stdlib.h>
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
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Connected to server!\n\n");

    // Fork to handle full-duplex communication
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        close(sockfd);
        exit(0);
    }

    // Child: Handle Receiving
    if (pid == 0) {
        char buffer[1024]; // Buffer for storing msg
        while (1) { // Infinite loop to keep receiving msgs
            memset(buffer, 0, sizeof(buffer));
            int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
            
            if (bytes_received <= 0) {
                printf("Server disconnected.\n");
                break;
            }
            if (strcmp(buffer, "exit") == 0) { // Check if client sent "exit"
                printf("Server sent exit command. Closing connection.\n");
                break;
            }
            printf("--Server:\n%s\n", buffer);
        }

        close(sockfd);
        exit(0);
    }
    // Parent: Handle Sending
    else {
        char msg[1024]; // Buffer for sending msg
        while (1) { // Infinite loop to keep sending msgs
            printf("--You:\n");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\n")] = 0;
            send(sockfd, msg, strlen(msg), 0);
            if (strcmp(msg, "exit") == 0) break;
        }
        close(sockfd);
    }

    printf("Disconnected from server...\n");

    return 0;
}
