import socket

def client_program():
    host = '127.0.0.1'  # server IP address
    port = 8080  # server port number

    # TODO: Create a socket object using socket.AF_INET and socket.SOCK_STREAM
    client_socket = # (Fill in this section)  # instantiate

    try:
        # TODO: Connect the client socket to the server using host and port
        # (Fill in this section)  # connect to the server
        print("Connected to the server")

        while True:
            message = input("Enter message to send to server (type 'disconnect' to disconnect): ")
            if message.lower() == 'disconnect':
                print("Disconnecting from the server")
                break

            # TODO: Send the message to the server using client_socket.send()
            # (Fill in this section)  # send message
            print("Message sent")

            # TODO: Receive the response from the server using client_socket.recv()
            # (Fill in this section)  # receive response
            print("Received from server: " + data)  # show response
    except Exception as e:
        print(f"Error: {e}")
    finally:
        # TODO: Close the client socket
        # (Fill in this section)  # close the connection
        print("Disconnected from the server")

if __name__ == '__main__':
    client_program()
