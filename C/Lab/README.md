
# Multi-threaded Client-Server Application Lab in C

## Introduction

In this lab, you will create a simple multi-threaded client-server application using C. The client will connect to the server, send messages, and receive responses. The server will handle multiple client connections concurrently and manage idle connections. You will fill in the missing parts of the provided code to complete the lab.

## Objectives

By the end of this lab, you will be able to:
- Set up a client-server architecture using sockets in C.
- Implement multi-threading to handle multiple client connections.
- Manage idle connections on the server.

## Prerequisites

- Basic understanding of C programming.
- Familiarity with socket programming in C.
- Understanding of threading in C (using `winsock2.h` for Windows).

## Files Provided

- `Client_Multi.c`: Contains the client code with placeholders for you to fill in.
- `Server_Multi.c`: Contains the server code with placeholders for you to fill in.

## Lab Steps

### 1. Setting Up the Client

1. Open `Client_Multi.c` in your favorite code editor.

2. Locate the first TODO comment:
   ```c
   // TODO: Create a socket object using AF_INET and SOCK_STREAM
   client_socket = // (Fill in this section)
   ```
   **Hint:** Use `socket(AF_INET, SOCK_STREAM, 0)` to create the socket object.

3. Locate the next TODO comment:
   ```c
   // TODO: Connect the client socket to the server using host and port
   // (Fill in this section)
   ```
   **Hint:** Use `connect(client_socket, (struct sockaddr *)&server, sizeof(server))` to connect to the server.

4. Locate the following TODO comment:
   ```c
   // TODO: Send the message to the server using send()
   // (Fill in this section)
   ```
   **Hint:** Use `send(client_socket, message, strlen(message), 0)` to send the message.

5. Locate the next TODO comment:
   ```c
   // TODO: Receive the response from the server using recv()
   // (Fill in this section)
   ```
   **Hint:** Use `recv(client_socket, server_reply, sizeof(server_reply), 0)` to receive the response.

6. Locate the final TODO comment:
   ```c
   // TODO: Close the client socket
   // (Fill in this section)
   ```
   **Hint:** Use `closesocket(client_socket)` to close the connection.

7. Save your changes and close the file.

### 2. Setting Up the Server

1. Open `Server_Multi.c` in your favorite code editor.

2. Locate the first TODO comment:
   ```c
   // TODO: Create a socket object using AF_INET and SOCK_STREAM
   server_socket = // (Fill in this section)
   ```
   **Hint:** Use `socket(AF_INET, SOCK_STREAM, 0)` to create the socket object.

3. Locate the next TODO comment:
   ```c
   // TODO: Bind the socket to the host and port
   // (Fill in this section)
   ```
   **Hint:** Use `bind(server_socket, (struct sockaddr *)&server, sizeof(server))` to bind the socket.

4. Locate the following TODO comment:
   ```c
   // TODO: Make the socket listen for incoming connections
   // (Fill in this section)
   ```
   **Hint:** Use `listen(server_socket, 3)` to make the socket listen for connections.

5. Locate the final TODO comment:
   ```c
   // TODO: Accept a new connection
   *client_socket = // (Fill in this section)
   ```
   **Hint:** Use `accept(server_socket, (struct sockaddr *)&client, &c)` to accept a new connection.

6. Save your changes and close the file.

### 3. Running the Application

1. Open a terminal or command prompt.

2. Navigate to the directory containing your `Client_Multi.c` and `Server_Multi.c` files.

3. Compile the server program by running the following command:
   ```sh
   gcc -o server Server_Multi.c -lws2_32
   ```
   You should see a message indicating successful compilation.

4. Start the server by running the following command:
   ```sh
   ./server
   ```
   You should see a message indicating that the server is listening for connections.

5. Open another terminal or command prompt.

6. Compile the client program by running the following command:
   ```sh
   gcc -o client Client_Multi.c -lws2_32
   ```
   You should see a message indicating successful compilation.

7. Start the client by running the following command:
   ```sh
   ./client
   ```
   You should see a message indicating that the client has connected to the server.

8. Follow the prompts to send messages from the client to the server. You should see the server echo the messages back to the client.

9. Type `disconnect` in the client to disconnect from the server.

## Conclusion

Congratulations! You have successfully set up a multi-threaded client-server application in C. This lab has helped you understand the basics of socket programming and threading in C, and how to manage multiple client connections concurrently.
