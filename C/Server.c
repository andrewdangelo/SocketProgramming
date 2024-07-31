// Server side C program to demonstrate Socket programming
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

    SOCKET server_fd = INVALID_SOCKET;
    SOCKET new_socket = INVALID_SOCKET;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Forcefully attaching socket to the port 9090
    iResult = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
    if (iResult == SOCKET_ERROR) {
        printf("Setsockopt error: %ld\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 9090
    iResult = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if (iResult == SOCKET_ERROR) {
        printf("Bind failed: %ld\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed: %ld\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept failed: %ld\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    int valread = recv(new_socket, buffer, sizeof(buffer) - 1, 0); // subtract 1 for the null terminator at the end
    if (valread > 0) {
        buffer[valread] = '\0'; // Null-terminate the received data
        printf("%s\n", buffer);
    } else if (valread == 0) {
        printf("Connection closed\n");
    } else {
        printf("Recv failed: %ld\n", WSAGetLastError());
    }

    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    closesocket(new_socket);
    // closing the listening socket
    closesocket(server_fd);

    WSACleanup();

    return 0;
}
