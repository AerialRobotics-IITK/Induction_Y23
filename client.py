import socket
import os
import threading
import numpy as np

server_address = socket.gethostbyname(socket.gethostname())
server_port = 6069
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((server_address, server_port))
server_socket.listen()
print(f"The server is now live at {server_address}:{server_port}")

connected_clients = []
user_database = np.array(["user1"])
password_database = np.array(["pass1"])
banned_users = np.array["banned1"]
banned_passwords = np.array["bannedpass1"]

def send_file_list(client_socket, address):
    files = os.listdir()
    file_list = "\n".join(files)
    client_socket.send(file_list.encode())

def handle_retrieve_command(client_socket, address, filename):
    try:
        with open(filename, 'rb') as file:
            file_content = file.read()
            client_socket.send(file_content)
            print(f"{filename} has been sent to {address}")
    except FileNotFoundError:
        client_socket.send("File not found".encode())
        print(f"{filename} was not found")

def handle_store_command(client_socket, address, filename):
    files_exist = os.listdir()
    files_list = "\n".join(files_exist)
    files = files_list.split("\n")

    for file in files:
        if file == filename:
            client_socket.send("FileExists".encode())
            return

    client_socket.send("OK".encode())
    file_content = client_socket.recv(1024)
    with open(filename, 'wb') as file:
        file.write(file_content)
        print(f"{filename} has been received from {address} and saved successfully")

def handle_valid_client(client_socket, address):
    while True:
        client_socket.send("Command?".encode())
        message = client_socket.recv(1024).decode()
        if not message:
            continue

        command, *args = message.split()

        if command == "LIST":
            send_file_list(client_socket, address)

        elif command == "STOR":
            filename = args[0]
            handle_store_command(client_socket, address, filename)

        elif command == "RETR":
            filename = args[0]
            handle_retrieve_command(client_socket, address, filename)

        elif command == "QUIT":
            client_socket.close()
        else:
            client_socket.send("Invalid command!".encode())
            continue
        

def accept_and_authenticate():
    while True:
        client_socket, address = server_socket.accept()
        print(f"{address} has connected to the server")
        client_socket.send("Username?".encode())
        username = client_socket.recv(1024).decode()
        client_socket.send("Password?".encode())
        password = client_socket.recv(1024).decode()

            client_socket.send("UsernameValid".encode())
            t = threading.Thread(target=handle_valid_client, args=(client_socket, address))
            t.start()

            index = np.where(user_database == username)[0]
            if password_database[index[0]] == password:
                client_socket.send("UsernameValid".encode())
                t = threading.Thread(target=handle_valid_client, args=(client_socket, address))
                t.start()

            else:
                client_socket.send("UsernameInvalid".encode())
                client_socket.close()

accept_and_authenticate()
