#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define IDLE_TIMEOUT 30

volatile LONG active_connections = 0; // Use LONG type
HANDLE idle_event;
HANDLE server_running_event;

unsigned __stdcall handle_client(void *client_socket) {
    SOCKET conn = *(SOCKET *)client_socket;
    free(client_socket);
    char buffer[1024];
    int bytes_received;

    printf("Client connected.\n");

    while (1) {
        bytes_received = recv(conn, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received from client: %s\n", buffer);
        const char *response = "Hello from server";
        send(conn, response, strlen(response), 0);
        printf("Hello message sent\n");
    }

    closesocket(conn);
    InterlockedDecrement(&active_connections); // Explicitly use LONG
    if (active_connections == 0) {
        SetEvent(idle_event);
    }
    printf("Client disconnected.\n");

    return 0;
}

unsigned __stdcall idle_check(void *param) {
    while (WaitForSingleObject(server_running_event, 0) == WAIT_OBJECT_0) {
        WaitForSingleObject(idle_event, INFINITE);
        ResetEvent(idle_event);
        Sleep(IDLE_TIMEOUT * 1000);
        if (active_connections == 0) {
            printf("No active connections for 30 seconds. Shutting down server.\n");
            SetEvent(server_running_event);
            closesocket(*(SOCKET *)param);
            break;
        }
    }
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, *client_socket;
    struct sockaddr_in server, client;
    int c = sizeof(struct sockaddr_in);

    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server, sizeof(server));
    listen(server_socket, 3);

    idle_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    server_running_event = CreateEvent(NULL, TRUE, TRUE, NULL);

    _beginthreadex(NULL, 0, idle_check, (void *)&server_socket, 0, NULL);

    printf("Server listening on port %d\n", PORT);

    while (WaitForSingleObject(server_running_event, 0) == WAIT_OBJECT_0) {
        client_socket = malloc(sizeof(SOCKET));
        if (client_socket == NULL) {
            perror("Failed to allocate memory");
            break;
        }

        *client_socket = accept(server_socket, (struct sockaddr *)&client, &c);
        if (*client_socket == INVALID_SOCKET) {
            free(client_socket);
            break;
        }

        InterlockedIncrement(&active_connections); // Explicitly use LONG
        ResetEvent(idle_event);
        _beginthreadex(NULL, 0, handle_client, (void *)client_socket, 0, NULL);
    }

    // Ensure all resources are cleaned up
    closesocket(server_socket);
    WSACleanup();
    CloseHandle(idle_event);
    CloseHandle(server_running_event);

    printf("Server terminated.\n");

    return 0;
}
