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
