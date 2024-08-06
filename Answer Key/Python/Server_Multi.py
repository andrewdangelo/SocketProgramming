import socket
import threading
import time

def handle_client(conn, address, active_connections, idle_event, server_running):
    """
    Function to handle communication with a connected client.
    
    Parameters:
    conn (socket): The socket object for the connection.
    address (tuple): The address of the connected client.
    active_connections (list): The list of currently active connections.
    idle_event (threading.Event): Event to signal when the server is idle.
    server_running (threading.Event): Event to signal whether the server is running.
    """
    print("Connection from:", address)
    try:
        while True:
            data = conn.recv(1024).decode()  # Receive message from the client
            if not data:
                break  # If no data is received, break the loop
            print("Received from client:", data)
            message = "Hello from server"
            conn.send(message.encode())  # Send response to the client
            print("Hello message sent")
    except ConnectionResetError:
        print(f"Connection from {address} was reset.")
    finally:
        conn.close()  # Close the connection
        active_connections.remove(conn)  # Remove the connection from the list of active connections
        print(f"Connection from {address} closed.")
        if not active_connections and server_running.is_set():  # If no active connections, set the idle event
            idle_event.set()

def server_program():
    """
    Main function to start the server program.
    """
    host = '0.0.0.0'  # Listen on all available network interfaces
    port = 8080  # Port number to listen on
    idle_timeout = 30  # Timeout in seconds for the server to shut down when idle

    # Create a TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((host, port))  # Bind the socket to the address and port

    server_socket.listen(3)  # Listen for incoming connections (up to 3 in the queue)
    print("Server listening on port", port)

    active_connections = []  # List to keep track of active client connections
    idle_event = threading.Event()  # Event to signal when the server is idle
    server_running = threading.Event()  # Event to signal whether the server is running
    server_running.set()  # Initially, set the server as running

    def idle_check():
        """
        Function to check if the server has been idle for more than the specified timeout.
        """
        while server_running.is_set():  # Check if the server is still running
            idle_event.wait()  # Wait for the idle event to be set
            idle_event.clear()  # Clear the idle event
            time.sleep(idle_timeout)  # Wait for the idle timeout
            if not active_connections:  # If there are no active connections, shut down the server
                print("No active connections for 30 seconds. Shutting down server.")
                server_running.clear()  # Signal that the server should stop
                server_socket.close()  # Close the server socket
                break

    # Start the idle check thread
    idle_thread = threading.Thread(target=idle_check, daemon=True)
    idle_thread.start()

    try:
        while server_running.is_set():  # Check if the server is still running
            try:
                conn, address = server_socket.accept()  # Accept a new connection
                idle_event.clear()  # Clear the idle event as there is an active connection
                active_connections.append(conn)  # Add the connection to the list of active connections
                # Start a new thread to handle the client
                client_thread = threading.Thread(target=handle_client, args=(conn, address, active_connections, idle_event, server_running))
                client_thread.start()
            except OSError:
                break  # Exit the loop if the server socket is closed
    finally:
        server_running.clear()  # Ensure the server running flag is cleared

        # Wait for all active connections to close
        for conn in active_connections:
            conn.close()

if __name__ == '__main__':
    server_program()
