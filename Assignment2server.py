import socket
import threading
import os

users = {'admin' : 'admin', 'user1':'pass1','user2':'pass2'}
BannedUsers = set()
AdminUsername = 'admin'

def handle_user(username, password):
        if username in BannedUsers:
            return 'User is banned. Cannot login'
        elif username in users and users.get(username)==password:
            return '331 User authentication successfull.'
        else:
            return 'Username not found'

def list_files():
    files = os.listdir(os.getcwd())
    return '\n'.join(files)

def retr_file(filename):
    if os.path.exists(filename):
        with open(filename, 'rb') as file:
            return file.read()
    else:
        return 'Such File does not exist in the directory.'

def store_file(filename, data):
    if os.path.exists(filename):
        return 'This File already exists.'
    else:
        with open(filename, 'wb') as file:
            file.write(data)
        return 'File transfer successful.'

def addUser(username,password):
    if username in users:
        return 'User already exists'
    else:
        users[username] = password
        return 'User added'

def deleteUser(username):
    if username in users:
        del users[username]
        return 'User deleted'
    else:
        return "User doesn't exist"

def banUser(username):
    if username != AdminUsername and username in users:
        BannedUsers.add(username)
        return 'User banned'
    else:
        return "User can't be banned"

def unbanUser(username):
    if username in BannedUsers:
        BannedUsers.remove(username)
        return 'User unbanned'
    else:
        return "User can't be unbanned"

def handle_command(command):
    parts = command.split()
    if parts[0] == 'USER':
        username = parts[1]
        password = parts[2]
        return handle_user(username,password)
    elif parts[0] == 'LIST':
        return list_files()
    elif parts[0] == 'RETR':
        return retr_file(filename)
    elif parts[0] == 'STOR':
        filename = parts[1]
        data = parts[2].encode()
        return store_file(filename, data)
    elif parts[0] == 'ADDUSER' and username==AdminUsername:
        new_username = parts[1]
        new_password = parts [2]
        return addUser(new_username, new_password)
    elif parts[0] == 'DELUSER' and username==AdminUsername:
        del_username = parts[1]
        return deleteUser(del_username)
    elif parts[0] == 'BAN' and username==AdminUsername:
        ban_user = parts[1]
        return banUser(ban_user)
    elif parts[0] == 'UNBAN' and username==AdminUsername:
        unban_user = parts[0]
        return unbanUser(unban_user)
    elif parts[0] == 'QUIT':
        return "QUIT"
    else:
        return 'Unidentified command'

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_ADDR = socket.gethostbyname(socket.gethostname())
    port = 2323
    server.bind((IP_ADDR,port))
    server.listen(5)
    print("Server is listening...")
    while True:
        client, address = server.accept()
        print(f"Connection recieved from: {address}")
        client_thread = threading.Thread(target=handle_client,args=(client,address))
        client_thread.start()

def handle_client(client, address):
    username = None
    client.send("You are connected to the server.\n".encode())
    while True:
        command = client.recv(1024).decode().strip()
        response=handle_command(command)
        if not command:
            break
        if response == 'QUIT':
            client.sendall('Goodbye!\n'.encode())
            break
        elif response.startswith('Enter Password'):
            client.send(response.encode()+b'\n')
            username = command.split()[1]
        else:
            client.send(response.encode()+b'\n')
    client.close()
    print(f"Connection disconneted from {address}")

if __name__ == "__main__":
    main()
