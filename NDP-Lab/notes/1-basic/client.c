#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>  // For inet_pton()

#define PORT 3300

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    serv_addr.sin_family = AF_INET;   // Same family as server code (or Address Family not supported)
    serv_addr.sin_port = htons(PORT); // Same port as server code (or ECONNREFUSED)
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); // Local connection (if wrong: connection times out)

    // Connect to server
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Connected to server!\n");

    // Send message
    char msg[1024]; // Input
    // char *msg = "Hello from Server"; // Hardcoded
    printf("Enter message to send: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;
    send(sockfd, msg, strlen(msg), 0);
    printf("Message sent to server! Awaiting response...\n\n");

    // Receive message
    char buffer[1024] = {0};
    recv(sockfd, buffer, sizeof(buffer), 0);
    // read(newsock, buffer, sizeof(buffer));
    printf("Server: %s\n\n", buffer);

    // Close socket
    close(sockfd);
    printf("Disconnected from server...\n");

    return 0;
}

// int num;
// printf("Enter an integer to send (0 to exit): ");
// scanf("%d", &num);

// // Exit condition
// if (num == 0) break;

// // Convert to network byte order and send
// int send_num = htonl(num);
// send(sockfd, &send_num, sizeof(send_num), 0);

// // Receive modified integer from server
// int recv_num = 0;
// recv(sockfd, &recv_num, sizeof(recv_num), 0);
// recv_num = ntohl(recv_num); // Convert to host byte order
// printf("Received from server: %d\n", recv_num);