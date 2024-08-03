
# Socket Programming and Multi-threaded Client-Server Applications

## Introduction

This repository contains materials and lab exercises focused on socket programming using both Python and C. Socket programming is a way of connecting two nodes on a network to communicate with each other. One socket (node) listens on a particular port at an IP, while the other socket reaches out to the other to form a connection. These are commonly known as server and client sockets.

## Berkeley Sockets

Berkeley sockets, also known as BSD sockets, are a de facto standard for socket programming. They provide a set of API functions for creating and managing network connections, allowing for communication between applications over a network.

Key concepts in Berkeley sockets include:
- **Socket Creation**: Using the `socket()` function to create a socket.
- **Binding**: Associating a socket with a specific port using the `bind()` function.
- **Listening**: Waiting for incoming connections using the `listen()` function.
- **Accepting Connections**: Accepting incoming connections using the `accept()` function.
- **Sending and Receiving Data**: Using the `send()` and `recv()` functions to communicate data between sockets.

## Python Lab: Multi-threaded Client-Server Application

The Python lab guides you through creating a multi-threaded client-server application. You will learn to:
- Set up a client-server architecture using Python's `socket` module.
- Implement multi-threading to handle multiple client connections.
- Manage idle connections on the server.

### Files Provided
- `Client_Multi.py`: Contains the client code with placeholders for you to fill in.
- `Server_Multi.py`: Contains the server code with placeholders for you to fill in.

For detailed instructions on the Python lab, refer to the `README_Python.md` file.

## C Lab: Multi-threaded Client-Server Application

The C lab guides you through creating a multi-threaded client-server application using C. You will learn to:
- Set up a client-server architecture using sockets in C.
- Implement multi-threading to handle multiple client connections.
- Manage idle connections on the server.

### Files Provided
- `Client_Multi.c`: Contains the client code with placeholders for you to fill in.
- `Server_Multi.c`: Contains the server code with placeholders for you to fill in.

For detailed instructions on the C lab, refer to the `README_C.md` file.

## Conclusion

By working through these labs, you will gain a solid understanding of socket programming and how to create robust, multi-threaded client-server applications in both Python and C. This knowledge is fundamental for network programming and is widely applicable in various fields such as web development, cybersecurity, and distributed systems.

Happy Coding!
