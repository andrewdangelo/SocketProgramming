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
