import socket
import os
import threading
import numpy as np

IP_address = socket.gethostbyname(socket.gethostname())
PORT = 5050
#the socket object
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((IP_address,PORT))
server.listen()
print(f"Server is listening on {IP_address}:{PORT}")

clients = []
usernames = np.array(["prasun"])
passwords = np.array(["prasun"])

def sendList(client , address):
    files = os.listdir()
    files_list = "\n".join(files)
    client.send(files_list.encode())

def handle_RETR_command(client, address, filename):
    try:
        with open(filename, 'rb') as file:
            file_content = file.read()
            client.send(file_content)
            print(f"Sent {filename} to {address}")
    except FileNotFoundError:
        client.send("File not found".encode())
        print(f"File {filename} not found")

def handle_STOR_command(client, address, filename):
    files_exist = os.listdir()
    files_list = "\n".join(files_exist)
    files = files_list.split("\n")

    for file in files:
        if file == filename:
            client.send("FileExists".encode())
            return

    client.send("OK".encode())
    file_content = client.recv(1024)
    with open(filename, 'wb') as file:
        file.write(file_content)
        print(f"File {filename} received from {address} and saved successfully")




def handleValidClient(client , address):
    while True:
        client.send("Command?".encode())
        message = client.recv(1024).decode()
        if not message:
            continue

        command, *args = message.split()

        if command == "LIST":
            sendList(client, address)
            continue

        elif command == "STOR":
            filename = args[0]
            handle_STOR_command(client, address, filename)
            continue

        elif command == "RETR":
            filename = args[0]
            handle_RETR_command(client, address, filename)
            continue

        elif command == "QUIT":
            client.close()

        # elif command == "ADDUSER":
        #     new_username = args[0]
        #     new_password = args[1]
        #     usernames = np.append(usernames, new_username)
        #     passwords = np.append(passwords, new_password)

        # elif command == "DELUSER":
        #     toBeremoved = args[0]
        #     number = np.where(usernames== toBeremoved)[0]
        #     passwords = np.delete(passwords, number)
        #     usernames = np.delete(usernames, number)
            


        else:
            client.send("Invalid command!".encode())
            continue
        

def AcceptAndAuthenticate():

    while True:
        client, addressess = server.accept()
        print(f"{addressess} clientected to the server")
        client.send("User?".encode())
        username = client.recv(1024).decode()
        client.send("Pass?".encode())
        password = client.recv(1024).decode()

        # if username == "admin123" and password == "admin123":
        #     client.send("User valid".encode())
        #     t = threading.Thread(target=handleValidClient, args=(client , addressess))
        #     t.start()

        #else :
        index = np.where(usernames == username)[0]
        if passwords[index[0]] == password:
            client.send("User valid".encode())
            t = threading.Thread(target=handleValidClient, args=(client , addressess))
            t.start()

        else:
            client.send("User Invalid".encode())
            client.close()
        

AcceptAndAuthenticate()