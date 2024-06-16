import socket
import os
import sys
import threading

users = {
    "admin" : "adminpassword"
}

def handle_client(client_socket, address):
    client_socket.send("Welcome to the FTP server\n".encode())
    username = None

    while True:
        data = client_socket.recv(1024).decode().strip()
        if not data:
            break

        command = data.split(" ")[0]
        if command == "USER":
            username = data.split(" ")[1]
            if username in users:
                client_socket.send("Password required for {}\n".format(username).encode())
            else:
                client_socket.send("Invalid username\n".encode())
        elif command == "PASS":
            password = data.split(" ")[1]
            if password == users[username]:
                client_socket.send("User logged in\n".encode())
            else:
                client_socket.send("Invalid password\n".encode())
        elif command == "LIST":
            files = os.listdir(".")
            client_socket.send("OK\n".encode())
            for file in files:
                client_socket.send("{}\n".format(file).encode())
            client_socket.send("List transfer done\n".encode())
        elif command == "RETR":
            filename = data.split(" ")[1]
            if os.path.exists(filename):
                client_socket.send("OK\n".encode())
                with open(filename, "rb") as file:
                    client_socket.send(file.read())
                client_socket.send("File transfer done\n".encode())
            else:
                client_socket.send("File not found\n".encode())
        elif command == "STOR":
            filename = data.split(" ")[1]
            client_socket.send("OK\n".encode())
            with open(filename, "wb") as file:
                file.write(client_socket.recv(1024))
            client_socket.send("File transfer done\n".encode())
        elif command == "QUIT":
            client_socket.send("Goodbye\n".encode())
            break
        else:
            client_socket.send("Unknown command\n".encode())

    client_socket.close()

def main():
    host = "127.0.0.1"
    port = 12345

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)

    print("Listening on {}:{}".format(host, port))

    while True:
        client_socket, address = server_socket.accept()
        print("Accepted connection from {}:{}".format(address[0], address[1]))

        client_thread = threading.Thread(target=handle_client, args=(client_socket, address))
        client_thread.start()

if __name__ == "__main__":
    main()

