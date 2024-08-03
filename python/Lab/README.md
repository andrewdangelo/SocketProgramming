
# Multi-threaded Client-Server Application Lab

## Introduction

In this lab, you will create a simple multi-threaded client-server application using Python's `socket` and `threading` modules. The client will connect to the server, send messages, and receive responses. The server will handle multiple client connections concurrently and manage idle connections. You will fill in the missing parts of the provided code to complete the lab.

## Objectives

By the end of this lab, you will be able to:
- Set up a client-server architecture using sockets.
- Implement multi-threading to handle multiple client connections.
- Manage idle connections on the server.

## Prerequisites

- Basic understanding of Python programming.
- Familiarity with socket programming in Python.
- Understanding of threading in Python.

## Files Provided

- `Client_Multi.py`: Contains the client code with placeholders for you to fill in.
- `Server_Multi.py`: Contains the server code with placeholders for you to fill in.

## Lab Steps

### 1. Setting Up the Client

1. Open `Client_Multi.py` in your favorite code editor.

2. Locate the first TODO comment:
   ```python
   # TODO: Create a socket object using socket.AF_INET and socket.SOCK_STREAM
   client_socket = # (Fill in this section)  # instantiate
   ```
   **Hint:** Use `socket.socket(socket.AF_INET, socket.SOCK_STREAM)` to create the socket object.

3. Locate the next TODO comment:
   ```python
   # TODO: Connect the client socket to the server using host and port
   # (Fill in this section)  # connect to the server
   ```
   **Hint:** Use `client_socket.connect((host, port))` to connect to the server.

4. Locate the following TODO comment:
   ```python
   # TODO: Send the message to the server using client_socket.send()
   # (Fill in this section)  # send message
   ```
   **Hint:** Use `client_socket.send(message.encode())` to send the message.

5. Locate the next TODO comment:
   ```python
   # TODO: Receive the response from the server using client_socket.recv()
   # (Fill in this section)  # receive response
   ```
   **Hint:** Use `client_socket.recv(1024).decode()` to receive the response.

6. Locate the final TODO comment:
   ```python
   # TODO: Close the client socket
   # (Fill in this section)  # close the connection
   ```
   **Hint:** Use `client_socket.close()` to close the connection.

7. Save your changes and close the file.

### 2. Setting Up the Server

1. Open `Server_Multi.py` in your favorite code editor.

2. Locate the first TODO comment:
   ```python
   # TODO: Create a socket object using socket.AF_INET and socket.SOCK_STREAM
   server_socket = # (Fill in this section)
   ```
   **Hint:** Use `socket.socket(socket.AF_INET, socket.SOCK_STREAM)` to create the socket object.

3. Locate the next TODO comment:
   ```python
   # TODO: Bind the socket to the host and port
   # (Fill in this section)
   ```
   **Hint:** Use `server_socket.bind((host, port))` to bind the socket.

4. Locate the following TODO comment:
   ```python
   # TODO: Make the socket listen for incoming connections
   # (Fill in this section)
   ```
   **Hint:** Use `server_socket.listen(5)` to make the socket listen for connections.

5. Locate the final TODO comment:
   ```python
   # TODO: Accept a new connection
   conn, address = # (Fill in this section)  # Accept a new connection
   ```
   **Hint:** Use `server_socket.accept()` to accept a new connection.

6. Save your changes and close the file.

### 3. Running the Application

1. Open a terminal or command prompt.

2. Navigate to the directory containing your `Client_Multi.py` and `Server_Multi.py` files.

3. Start the server by running the following command:
   ```sh
   python Server_Multi.py
   ```
   You should see a message indicating that the server is listening for connections.

4. Open another terminal or command prompt.

5. Start the client by running the following command:
   ```sh
   python Client_Multi.py
   ```
   You should see a message indicating that the client has connected to the server.

6. Follow the prompts to send messages from the client to the server. You should see the server echo the messages back to the client.

7. Type `disconnect` in the client to disconnect from the server.

## Conclusion

Congratulations! You have successfully set up a multi-threaded client-server application. This lab has helped you understand the basics of socket programming and threading in Python, and how to manage multiple client connections concurrently.
