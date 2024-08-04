
# Introduction to Socket Programming with C

## Overview

Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket (node) listens on a particular port at an IP address, while the other socket reaches out to the other to form a connection. In C, the Berkeley sockets API provides a powerful and flexible way to implement socket programming.

In this tutorial, we will cover basic client-server communication using sockets in C. We will compare this with Berkeley socket primitives and explain the provided C code for both client and server.

## Comparison to Berkeley Socket Primitives

The Berkeley sockets API is a de facto standard for socket programming. It includes functions like `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, and `recv()`. These functions are directly used in C, making it a robust way to manage network communication.

- **socket()**: Create a new socket using the given address family, socket type, and protocol number.
- **bind()**: Bind the socket to an address (IP address and port number).
- **listen()**: Enable a server to accept connections. It specifies the number of unaccepted connections that the system will allow before refusing new connections.
- **accept()**: Accept a connection from a client.
- **connect()**: Connect the socket to a server.
- **send()**: Send data through the socket.
- **recv()**: Receive data from the socket.

## Explanation of the Code

### Server Code (`Server.c`)

1. **Include Necessary Headers**: The code includes headers like `<stdio.h>`, `<stdlib.h>`, `<string.h>`, and socket-specific headers `<winsock2.h>` and `<ws2tcpip.h>`.

2. **Initialize Winsock**: `WSAStartup` is used to initialize the Winsock library, which is required for network programming in Windows.

3. **Create Socket**: `socket()` function is used to create a socket.

4. **Bind Socket**: `bind()` function binds the socket to a specific port and IP address.

5. **Listen for Connections**: `listen()` function listens for incoming connection requests.

6. **Accept Connections**: `accept()` function accepts an incoming connection request.

7. **Receive Data**: `recv()` function receives data from the client.

8. **Send Data**: `send()` function sends data to the client.

9. **Clean Up**: `closesocket()` and `WSACleanup()` functions are used to clean up resources.

### Client Code (`Client.c`)

1. **Include Necessary Headers**: The code includes headers like `<stdio.h>`, `<stdlib.h>`, `<string.h>`, and socket-specific headers `<winsock2.h>` and `<ws2tcpip.h>`.

2. **Initialize Winsock**: `WSAStartup` is used to initialize the Winsock library.

3. **Create Socket**: `socket()` function is used to create a socket.

4. **Connect to Server**: `connect()` function connects the socket to the server's address and port.

5. **Send Data**: `send()` function sends data to the server.

6. **Receive Data**: `recv()` function receives data from the server.

7. **Clean Up**: `closesocket()` and `WSACleanup()` functions are used to clean up resources.

### How the Code Works

1. **Server (`Server.c`)**:
    - The server binds to `INADDR_ANY` (all available interfaces) on port `9090`.
    - It listens for incoming connections with a backlog of 3 connections.
    - When a client connects, the server accepts the connection and receives a message.
    - The server sends a response back to the client and then closes the connection.

2. **Client (`Client.c`)**:
    - The client connects to the server at `127.0.0.1` (localhost) on port `9090`.
    - It sends a "Hello from client" message to the server.
    - The client receives a response from the server and prints it.
    - Finally, the client closes the connection.

### How to Run the Code

1. **Compile the Server**:
    - Open a terminal or command prompt.
    - Navigate to the directory where `Server.c` is located.
    - Compile the server code using a C compiler like `gcc`:
      ```sh
      gcc -o server Server.c -lws2_32
      ```

2. **Compile the Client**:
    - Open another terminal or command prompt.
    - Navigate to the directory where `Client.c` is located.
    - Compile the client code using a C compiler like `gcc`:
      ```sh
      gcc -o client Client.c -lws2_32
      ```

3. **Start the Server**:
    - Run the server executable:
      ```sh
      ./server
      ```

4. **Run the Client**:
    - Open another terminal or command prompt.
    - Run the client executable:
      ```sh
      ./client
      ```

5. **Observe the Output**:
    - The server terminal should display a message indicating it is listening on port `9090` and the connection details.
    - The client terminal should display the sent message and the response from the server.

By following these steps, you can observe a simple client-server communication using sockets in C.
