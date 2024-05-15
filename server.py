import socket
import os

def receive_list(client):
    files_list = client.recv(1024).decode()
    files = files_list.split("\n")
    return files

def send_file(client, filename):
    with open(filename, 'rb') as file:
        file_content = file.read()
        client.send(file_content)
        print("File sent successfully")

def retrieve_file(client, filename):
    file_content = client.recv(1024)
    with open(filename, 'wb') as file:
        file.write(file_content)
    print("File retrieved successfully!")

def user():
    username_input = input("Enter your username: ")
    password_input = input("Enter your password: ")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    SERVER_IP = "127.0.0.1"  # Replace with your server IP
    SERVER_PORT = 6069

    client_socket.connect((SERVER_IP, SERVER_PORT))

    while True:
        message = client_socket.recv(1024).decode()
        
        if message == "EnterUsername":
            client_socket.send(username_input.encode())

        elif message == "EnterPassword":
            client_socket.send(password_input.encode())

        elif message == "UsernameValid":
            print("Authentication Successful!")
            print("1. LIST: List all files in the current directory.\n2. RETR <filename>: Retrieve a file from the server.\n3. STOR <filename>: Store a file on the server.\n4. QUIT: Disconnect from the server.")

        elif message == "EnterCommand":
            command = input("\nEnter a valid command: ")
            client_socket.send(command.encode())
            command_type, *args = command.split()

            if command_type == "LIST":
                files = receive_list(client_socket)
                print("\nList of files on the server:")
                for file in files:
                    print(file)
                continue

            elif command_type == "RETR":
                filename = args[0]
                retrieve_file(client_socket, filename)
                continue

            elif command_type == "STOR":
                continue
            
            elif command_type == "QUIT":
                print("[DISCONNECTING] Disconnecting from server...")
                client_socket.close()
                break

            else:
                continue
        
        elif message == "OK":
            filename = args[0]
            send_file(client_socket, filename)
            continue

        elif message == "FileNotFound":
            print("The requested file does not exist. Please check again.")
            continue

        elif message == "FileExists":
            print("The file already exists on the server!")
            continue

        elif message == "InvalidCommand":
            print("Please enter a valid command!")
            continue
        
        elif message == "UsernameInvalid":
            print("Authentication unsuccessful! Please try again.")
            client_socket.close()
            break

user()