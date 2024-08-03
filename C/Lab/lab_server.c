#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define IDLE_TIMEOUT 30

HANDLE idle_event, server_running_event;
LONG active_connections = 0;

unsigned __stdcall handle_client(void *param) {
    SOCKET client_socket = *(SOCKET *)param;
    char client_message[1024], server_reply[1024];
    int recv_size;

    free(param);

    while ((recv_size = recv(client_socket, client_message, sizeof(client_message), 0)) > 0) {
        client_message[recv_size] = '\0';
        printf("Received from client: %s\n", client_message);
        sprintf(server_reply, "Echo: %s", client_message);
        send(client_socket, server_reply, strlen(server_reply), 0);
        SetEvent(idle_event);
    }

    closesocket(client_socket);
    InterlockedDecrement(&active_connections);
    SetEvent(idle_event);
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

    // TODO: Create a socket object using AF_INET and SOCK_STREAM
    server_socket = // (Fill in this section)

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // TODO: Bind the socket to the host and port
    // (Fill in this section)

    // TODO: Make the socket listen for incoming connections
    // (Fill in this section)
    printf("Server listening on port %d\n", PORT);

    idle_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    server_running_event = CreateEvent(NULL, TRUE, TRUE, NULL);

    _beginthreadex(NULL, 0, idle_check, (void *)&server_socket, 0, NULL);

    while (WaitForSingleObject(server_running_event, 0) == WAIT_OBJECT_0) {
        client_socket = malloc(sizeof(SOCKET));
        if (client_socket == NULL) {
            perror("Failed to allocate memory");
            break;
        }

        // TODO: Accept a new connection
        *client_socket = // (Fill in this section)
        if (*client_socket == INVALID_SOCKET) {
            free(client_socket);
            break;
        }

        InterlockedIncrement(&active_connections);
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
