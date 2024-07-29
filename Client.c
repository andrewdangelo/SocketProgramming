// Client side C program to demonstrate Socket programming
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9090

int main(int argc, char const* argv[]) {
    WSADATA wsaData;
    int iResult;

    SOCKET client_fd = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_fd == INVALID_SOCKET) {
        printf("Socket creation error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    iResult = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (iResult == SOCKET_ERROR) {
        printf("Connection failed: %ld\n", WSAGetLastError());
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    // Send data
    iResult = send(client_fd, hello, strlen(hello), 0);
    if (iResult == SOCKET_ERROR) {
        printf("Send failed: %ld\n", WSAGetLastError());
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }
    printf("Hello message sent\n");

    // Receive data
    iResult = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (iResult > 0) {
        buffer[iResult] = '\0'; // Null-terminate the received data
        printf("%s\n", buffer);
    } else if (iResult == 0) {
        printf("Connection closed\n");
    } else {
        printf("Recv failed: %ld\n", WSAGetLastError());
    }

    // Clean up
    closesocket(client_fd);
    WSACleanup();

    return 0;
}
