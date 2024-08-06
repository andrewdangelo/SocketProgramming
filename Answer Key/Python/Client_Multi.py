import socket

def client_program():
    host = '127.0.0.1'  # server IP address
    port = 8080  # server port number

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # instantiate

    try:
        client_socket.connect((host, port))  # connect to the server
        print("Connected to the server")

        while True:
            message = input("Enter message to send to server (type 'disconnect' to disconnect): ")
            if message.lower() == 'disconnect':
                print("Disconnecting from the server")
                break

            client_socket.send(message.encode())  # send message
            print("Message sent")

            data = client_socket.recv(1024).decode()  # receive response
            print("Received from server: " + data)  # show response
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()  # close the connection
        print("Disconnected from the server")

if __name__ == '__main__':
    client_program()

