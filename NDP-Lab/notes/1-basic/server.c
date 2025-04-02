#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // For htons(), struct sockaddr_in, INADDR_ANY
#include <sys/types.h>
#include <string.h>
#include <unistd.h> // For close() and read()
#include <arpa/inet.h> // For inet_ntoa(), inet_addr()

#define PORT 3300

int main() {
    int sockfd, newsock;
    struct sockaddr_in address, client_addr;
    socklen_t addrlen = sizeof(address), client_len = sizeof(client_addr);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // SO_REUSEADDR is set before bind()
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket to specific address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept on any IP
    address.sin_port = htons(PORT);       // Accept on specified port
    bind(sockfd, (struct sockaddr*)&address, sizeof(address)); // Use first struct for server

    // Listen for connectionsS
    listen(sockfd, 3);
    // printf("Server is listening on port %d...\n", PORT); // Can be done in getsockname()

    // getsockname(): gets IP and Port of current (server) socket
    struct sockaddr_in server_info;
    socklen_t server_info_len = sizeof(server_info);
    getsockname(sockfd, (struct sockaddr*)&server_info, &server_info_len);
    printf("Server is running on IP: %s, Port: %d\n\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    // Accept connection
    newsock = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&client_len); // Use diff struct for client
    // printf("Client connected!\n"); // Can be done in getpeername()

    // getpeername(): gets IP and Port of peer (client) socket
    struct sockaddr_in client_info;
    socklen_t client_info_len = sizeof(client_info);
    getpeername(newsock, (struct sockaddr*)&client_info, &client_info_len);
    printf("Client is connected from IP: %s, Port: %d\n\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    // Receive message
    char buffer[1024] = {0}; // To store msg from client
    recv(newsock, buffer, sizeof(buffer), 0);
    // read(newsock, buffer, sizeof(buffer));
    printf("Client: %s\n", buffer);

    // Send message
    char msg[1024]; // Input
    // char *msg = "Hello from Server"; // Hardcoded
    printf("Enter message to send: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;
    send(newsock, msg, strlen(msg), 0);
    printf("Message sent to client!\n\n");

    // Close sockets
    close(newsock);
    printf("Client connection closed.\n");
    close(sockfd);
    printf("Server socket closed. Shutting down...\n");

    return 0;
}

// // Receive integer from client
// int num = 0;
// int bytes_received = recv(newsock, &num, sizeof(num), 0);
// if (bytes_received <= 0) {
//     printf("Client disconnected.\n");
//     break;
// }
// num = ntohl(num); // Convert from network to host byte order
// printf("Client sent: %d\n", num);

// // Process the integer (e.g., add 1)
// num += 1;
// printf("Sending back: %d\n", num);

// // Send modified integer back to client
// int send_num = htonl(num); // Convert from host to network byte order
// send(newsock, &send_num, sizeof(send_num), 0);