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
            message = f"Echo: {data}"  # Create a response message
            conn.send(message.encode())  # Send the response back to the client
            idle_event.set()  # Set the idle event to reset the idle timeout
    except Exception as e:
        print(f"Error: {e}")
    finally:
        conn.close()  # Close the connection
        active_connections.remove(conn)  # Remove the connection from the list of active connections
        idle_event.set()  # Set the idle event to reset the idle timeout
        print("Connection closed:", address)

def server_program():
    host = '127.0.0.1'  # Server IP address
    port = 8080  # Server port number
    idle_timeout = 30  # Timeout for idle server (in seconds)

    # TODO: Create a socket object using socket.AF_INET and socket.SOCK_STREAM
    server_socket = # (Fill in this section)

    # TODO: Bind the socket to the host and port
    # (Fill in this section)

    # TODO: Make the socket listen for incoming connections
    # (Fill in this section)
    print(f"Server listening on {host}:{port}")

    active_connections = []  # List to keep track of active connections
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
                # TODO: Accept a new connection
                conn, address = # (Fill in this section)  # Accept a new connection
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
