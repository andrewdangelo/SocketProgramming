#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char message[1024], server_reply[1024];
    int recv_size;

    WSAStartup(MAKEWORD(2, 2), &wsa);

    while (1) {
        printf("Enter 'connect' to connect to the server, 'disconnect' to disconnect, or 'quit' to exit: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline character

        if (strcmp(message, "connect") == 0) {
            client_socket = socket(AF_INET, SOCK_STREAM, 0);
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = inet_addr("127.0.0.1");
            server.sin_port = htons(PORT);

            if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
                printf("Connection error\n");
                continue;
            }

            printf("Connected to the server\n");

            while (1) {
                printf("Enter message to send to server (type 'disconnect' to disconnect): ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0; // Remove newline character

                if (strcmp(message, "disconnect") == 0) {
                    printf("Disconnecting from the server\n");
                    break;
                }

                send(client_socket, message, strlen(message), 0);
                recv_size = recv(client_socket, server_reply, sizeof(server_reply), 0);
                if (recv_size <= 0) {
                    printf("Server disconnected\n");
                    break;
                }
                server_reply[recv_size] = '\0';
                printf("Received from server: %s\n", server_reply);
            }

            closesocket(client_socket);
            printf("Disconnected from the server\n");
        } else if (strcmp(message, "quit") == 0) {
            printf("Exiting the program\n");
            break;
        } else {
            printf("Invalid input. Please enter 'connect', 'disconnect', or 'quit'.\n");
        }
    }

    WSACleanup();

    return 0;
}
