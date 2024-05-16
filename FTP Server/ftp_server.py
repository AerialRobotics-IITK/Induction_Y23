import socket
import os
import threading

#This is a folder in my home directory.
dir = os.path.expanduser("~/files/")

ADMIN_username="Aerial_Robotics"
ADMIN_password="*IITK-AR*"

users={"u1":"p1", "u2":"p2" ,"u3":"p3"}

banned_users=set()

def USER(username, password):
    if username in banned_users:
        return False
    return users.get(username) == password

def LIST():
    files=os.listdir(dir)
    return "\n".join(files)

def RETR(filename):
    filepath=os.path.join(dir,filename)
    if os.path.isfile(filepath):
        with open(filepath,"rb") as file:
            return file.read()
    else:
        return b"File not found."

def STOR(filename,data):
    filepath=os.path.join(dir,filename)
    if not os.path.isfile(filepath):
        with open(filepath,"wb") as file:
            file.write(data)
        return "File stored."
    else:
        return "File already exists."

#ADMIN Functions

def ADDUSER(username,password):
    if username not in users:
        users[username]=password
        return "User added."
    else:
        return "User already exists."

def DELUSER(username):
    if username in users:
        del users[username]
        return "User deleted."
    else:
        return "User not found."

def BAN(username):
    banned_users.add(username)
    return "User banned."

def UNBAN(username):
    if username in banned_users:
        banned_users.remove(username)
        return "User unbanned."
    else:
        return "User not found in ban list."

def handle_command(command):
    parts=command.split()
    if parts[0] == "USER":
        username = parts[1]
        password = parts[2]
        if USER(username, password):
            return "Authentication successful."
        else:
            return "Authentication failed."
    elif parts[0]=="LIST":
        return LIST()
    elif parts[0]=="RETR":
        filename=parts[1]
        return RETR(filename)
    elif parts[0]=="STOR":
        filename=parts[1]
        data=parts[2].encode()
        return STOR(filename, data)
    elif parts[0]=="ADDUSER" and username==ADMIN_username:
        new_user=parts[1]
        new_password=parts[2]
        return ADDUSER(new_user, new_password)
    elif parts[0]=="DELUSER" and username==ADMIN_username:
        user_to_delete=parts[1]
        return DELUSER(user_to_delete)
    elif parts[0]=="BAN" and username==ADMIN_username:
        user_to_ban=parts[1]
        return BAN(user_to_ban)
    elif parts[0]=="UNBAN" and username==ADMIN_username:
        user_to_unban=parts[1]
        return UNBAN(user_to_unban)
    elif parts[0]=="QUIT":
        return "QUIT"
    else:
        return "Invalid command."

def handle_client(client_socket, client_address):
    username=None
    client_socket.send(b"Welcome to the FTP server.\n")

    while True:
        command=client_socket.recv(1024).decode().strip()
        print("Received command:",command)

        response=handle_command(command)

        if response=="QUIT":
            client_socket.send(b"QUIT\n")
            break
        elif response.startswith("Enter password"):
            client_socket.send(response.encode()+b"\n")
            username = command.split()[1]
        else:
            client_socket.send(response.encode()+b"\n")

    client_socket.close()
    print("Connection closed with", client_address)

def main():
    server_socket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_ADDR=socket.gethostbyname(socket.gethostname())
    server_socket.bind((IP_ADDR, 2121))
    server_socket.listen(5)
    print("Server is listening.")

    while True:
        client_socket,client_address=server_socket.accept()
        print("Accepted connection from",client_address)

        client_thread=threading.Thread(target=handle_client,args=(client_socket, client_address))
        client_thread.start()

if __name__=="__main__":
    main()
