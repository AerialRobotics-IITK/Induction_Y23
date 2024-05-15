import socket
import os
import threading

def receive_list(client):
    
    files_list = client.recv(1024).decode()
    files = files_list.split("\n")
    return files

def send_file(client, filename):
    with open(filename, 'rb') as file:
        file_content = file.read()
        client.send(file_content)
        print("File Stored Successfully")

def RETR_command(client, filename):
    file_content = client.recv(1024)
    with open(filename, 'wb') as file:
        file.write(file_content)
    print("File retrieved successfully!")

def user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_ADDR = socket.gethostbyname(socket.gethostname())
    PORT = 5050

    client.connect((IP_ADDR, PORT))

    while True:
        message = client.recv(1024).decode()
        
        if message == "User?":
            client.send(username.encode())

        elif message == "Pass?":
            client.send(password.encode())

        elif message == "User valid":
            print("Authentication Successful!")
            print("1. LIST: This command should list all the files in the current directory.\n2. RETR <filename>: This command should be used to retrieve a file from the server.\n3. STOR <filename>: This command should be used to store a file on the server.\n4. QUIT: This command should be used to disconnect from the server.")

        elif message == "Command?":
            command = input("\nEnter valid command: ")
            client.send(command.encode())
            commandtype, *args = command.split()

            if commandtype == "LIST":
                files = receive_list(client)
                print("\n**List of files on the server**:")
                for file in files:
                    print(file)
                continue

            elif commandtype == "RETR":
                filename = args[0]
                RETR_command(client, filename)
                continue

            elif commandtype == "STOR":
                continue
            
            elif commandtype == "QUIT":
                print("[DISCONNECTING] disconnecting from server...")
                client.close()

            else:
                continue
        
        elif message == "OK":
            filename = args[0]
            send_file(client, filename)
            continue

        elif message == "File not found":
            print("No such file was found. Check again")
            continue

        elif message == "FileExists":
            print("File Already Exists!")
            continue

        elif message == "Invalid command!":
            print("ENTER A VALID COMMAND!")
            continue
        
        elif message == "User Invalid":
            print("Authentication Unsuccessful!\nTRY AGAIN!")
            client.close()

def admin():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_ADDR = socket.gethostbyname(socket.gethostname())
    PORT = 5050

    client.connect((IP_ADDR, PORT))

    while True:
        message = client.recv(1024).decode()
        
        if message == "User?":
            client.send(username.encode())

        elif message == "Pass?":
            client.send(password.encode())

        elif message == "User valid":
            print("Authentication Successful!")
            print("1. LIST: This command should list all the files in the current directory.\n2. RETR <filename>: This command should be used to retrieve a file from the server.\n3. STOR <filename>: This command should be used to store a file on the server.\n4. QUIT: This command should be used to disconnect from the server.\n5. ADDUSER <username> <password>: This command should be used to add a new user to the server.\n6. DELUSER <username>: This command should be used to delete a user from the server.")

        elif message == "Command?":
            command = input("\nEnter valid command: ")
            client.send(command.encode())
            commandtype, *args = command.split()

            if commandtype == "LIST":
                files = receive_list(client)
                print("\n**List of files on the server**:")
                for file in files:
                    print(file)
                continue

            elif commandtype == "RETR":
                filename = args[0]
                RETR_command(client, filename)
                continue

            elif commandtype == "STOR":
                continue
            
            elif commandtype == "QUIT":
                print("[DISCONNECTING] disconnecting from server...")
                client.close()

            elif commandtype == "ADDUSER":
                print("New User Added Successfully")
                continue

            elif commandtype == "DELUSER":
                print("DELETED USER")
            
        elif message == "OK":
            filename = args[0]
            send_file(client, filename)
            continue

        elif message == "File not found":
            print("No such file was found. Check again")
            continue

        elif message == "FileExists":
            print("File Already Exists!")
            continue

        elif message == "Invalid command!":
            print("ENTER A VALID COMMAND!")
            continue
        
        elif message == "User Invalid":
            print("Authentication Unsuccessful!\nTRY AGAIN!")
            client.close()

# def main():
#     response = input("Press 1 for user login\nPress 2 for admin login\n")

#     if response == 1:
#         user()
#     elif response == 2:
#         admin()


user()