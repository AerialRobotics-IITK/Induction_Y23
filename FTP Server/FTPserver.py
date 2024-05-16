import socket
import threading
import os

# User database (replace with database integration for production)
users = {
    'admin': 'admin123',
    'user1': 'password1',
    'user2': 'password2'
}

# Admin database (replace with database integration for production)
admins = {
    'admin': 'admin123'
}


# Function to handle client requests
def handle_client(client_socket):
    # Authenticate user
    client_socket.send(b'220 Welcome to the FTP server\r\n')
    username = client_socket.recv(1024).decode().strip()
    if username in users:
        client_socket.send(b'331 Enter password\r\n')
        password = client_socket.recv(1024).decode().strip()
        if password == users[username]:
            client_socket.send(b'230 Login successful\r\n')
            if username == 'admin':
                handle_admin_commands(client_socket)
            else:
                handle_user_commands(client_socket)
        else:
            client_socket.send(b'530 Incorrect password\r\n')
            client_socket.close()
            return
    else:
        client_socket.send(b'530 User not found\r\n')
        client_socket.close()
        return

# Function to handle user commands
def handle_user_commands(client_socket):
    client_socket.send(b'230 User authentication successful. You can now execute user commands\r\n')
    while True:
        command = client_socket.recv(1024).decode().strip()
        if command.startswith('LIST'):
            list_files(client_socket)
        elif command.startswith('RETR'):
            retrieve_file(client_socket, command.split()[1])
        elif command.startswith('STOR'):
            store_file(client_socket, command.split()[1])
        elif command.startswith('QUIT'):
            client_socket.send(b'221 Goodbye\r\n')
            client_socket.close()
            break
        else:
            client_socket.send(b'500 Unknown command\r\n')

# List files in the current directory (user command)
def list_files(client_socket):
    files = os.listdir('.')
    file_list = '\n'.join(files)
    client_socket.send(file_list.encode())

# Retrieve a file from the server (user command)
def retrieve_file(client_socket, filename):
    try:
        with open(filename, 'rb') as file:
            data = file.read()
            client_socket.send(data)
    except FileNotFoundError:
        client_socket.send(b'550 File not found\r\n')

# Store a file on the server (user command)
def store_file(client_socket, filename):
    try:
        data = client_socket.recv(1024)
        with open(filename, 'wb') as file:
            file.write(data)
        client_socket.send(b'226 File stored successfully\r\n')
    except:
        client_socket.send(b'550 Error storing file\r\n')

            
    

# Function to handle admin commands
def handle_admin_commands(client_socket):
    client_socket.send(b'331 Enter admin password to proceed\r\n')
    admin_password = client_socket.recv(1024).decode().strip()
    if admin_password == admins.get('admin'):
        client_socket.send(b'230 Admin authentication successful. You can now execute admin commands\r\n')
        while True:
            command = client_socket.recv(1024).decode().strip()
            if command.startswith('ADDUSER'):
                add_user(client_socket, command.split()[1:])
            elif command.startswith('DELUSER'):
                delete_user(client_socket, command.split()[1])
            elif command.startswith('BAN'):
                ban_user(client_socket, command.split()[1])
            elif command.startswith('UNBAN'):
                unban_user(client_socket, command.split()[1])
            elif command.startswith('QUIT'):
                client_socket.send(b'221 Goodbye\r\n')
                client_socket.close()
                break
            else:
                client_socket.send(b'500 Unknown command\r\n')
    else:
        client_socket.send(b'530 Admin authentication failed\r\n')
        client_socket.close()

# Add a new user to the server (admin command)
def add_user(client_socket, args):
    if len(args) != 2:
        client_socket.send(b'501 Invalid parameters for ADDUSER\r\n')
    else:
        username, password = args
        if username not in users:
            users[username] = password
            client_socket.send(f'200 User {username} added successfully\r\n'.encode())
        else:
            client_socket.send(f'550 User {username} already exists\r\n'.encode())

# Delete a user from the server (admin command)
def delete_user(client_socket, username):
    if username in users:
        del users[username]
        client_socket.send(f'200 User {username} deleted successfully\r\n'.encode())
    else:
        client_socket.send(f'550 User {username} not found\r\n'.encode())

# Ban a user from the server (admin command)
def ban_user(client_socket, username):
    if username in users:
        users[username] = 'BANNED'
        client_socket.send(f'200 User {username} banned successfully\r\n'.encode())
    else:
        client_socket.send(f'550 User {username} not found\r\n'.encode())

# Unban a user from the server (admin command)
def unban_user(client_socket, username):
    if username in users and users[username] == 'BANNED':
        users[username] = 'UNBANNED'
        client_socket.send(f'200 User {username} unbanned successfully\r\n'.encode())
    else:
        client_socket.send(f'550 User {username} not found or not banned\r\n'.encode())

# Main server function
def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('127.0.0.1', 21))
    server.listen(5)
    print('FTP server started')
    while True:
        client_socket, addr = server.accept()
        print(f'Client connected: {addr}')
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == '__main__':
    main()
