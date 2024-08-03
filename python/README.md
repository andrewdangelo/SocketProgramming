
# Introduction to Socket Programming with Python

## Overview

Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket (node) listens on a particular port at an IP address, while the other socket reaches out to the other to form a connection. Python provides a powerful library, `socket`, which provides a low-level interface to the Berkeley sockets API.

In this tutorial, we will cover basic client-server communication using sockets in Python. We will compare this with Berkeley socket primitives and explain the provided Python code for both client and server.

## Comparison to Berkeley Socket Primitives

The Berkeley sockets API is a de facto standard for socket programming. It includes functions like `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, and `recv()`. These functions are mirrored in Python's `socket` module, making it easy for those familiar with Berkeley sockets to transition to Python.

- **socket()**: Create a new socket using the given address family, socket type, and protocol number.
- **bind()**: Bind the socket to an address (IP address and port number).
- **listen()**: Enable a server to accept connections. It specifies the number of unaccepted connections that the system will allow before refusing new connections.
- **accept()**: Accept a connection from a client.
- **connect()**: Connect the socket to a server.
- **send()**: Send data through the socket.
- **recv()**: Receive data from the socket.

## Explanation of the Code

### Server Code (`Server.py`)

```python
import socket

def server_program():
    host = '0.0.0.0'  # listen on all available interfaces
    port = 8080  # server port number

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # instantiate
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((host, port))  # bind to the port

    server_socket.listen(3)  # listen for incoming connections
    print("Server listening on port", port)

    conn, address = server_socket.accept()  # accept new connection
    print("Connection from:", address)
    
    try:
        data = conn.recv(1024).decode()  # receive message
        print("Received from client:", data)
        message = "Hello from server"
        conn.send(message.encode())  # send response
        print("Hello message sent")
    finally:
        conn.close()  # close the connection

if __name__ == '__main__':
    server_program()
```

### Client Code (`Client.py`)

```python
import socket

def client_program():
    host = '127.0.0.1'  # server IP address
    port = 8080  # server port number

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # instantiate
    client_socket.connect((host, port))  # connect to the server

    message = "Hello from client"

    try:
        client_socket.send(message.encode())  # send message
        print("Hello message sent")
        data = client_socket.recv(1024).decode()  # receive response
        print("Received from server: " + data)  # show response
    finally:
        client_socket.close()  # close the connection

if __name__ == '__main__':
    client_program()
```

### How the Code Works

1. **Server (`Server.py`)**:
    - The server binds to `0.0.0.0` (all available interfaces) on port `8080`.
    - It listens for incoming connections with a backlog of 3 connections.
    - When a client connects, the server accepts the connection and receives a message.
    - The server sends a response back to the client and then closes the connection.

2. **Client (`Client.py`)**:
    - The client connects to the server at `127.0.0.1` (localhost) on port `8080`.
    - It sends a "Hello from client" message to the server.
    - The client receives a response from the server and prints it.
    - Finally, the client closes the connection.

### How to Run the Code

1. **Start the Server**:
    - Open a terminal or command prompt.
    - Navigate to the directory where `Server.py` is located.
    - Run the server using the command:
      ```sh
      python Server.py
      ```

2. **Run the Client**:
    - Open another terminal or command prompt.
    - Navigate to the directory where `Client.py` is located.
    - Run the client using the command:
      ```sh
      python Client.py
      ```

3. **Observe the Output**:
    - The server terminal should display a message indicating it is listening on port `8080` and the connection details.
    - The client terminal should display the sent message and the response from the server.

By following these steps, you can observe a simple client-server communication using sockets in Python.
