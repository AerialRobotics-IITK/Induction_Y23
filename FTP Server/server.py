import socket
import threading
import time
import os

IP = socket.gethostbyname(socket.gethostname())
PORT = 3030
FORMAT = 'utf-8'
HEADER = 10
DISCONNECT_MESSAGE = "disconnect"

ADDR = (IP, PORT)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

def handle_client(conn, addr, user, pass_user,ban,unban):
    print(f"[New connection]: {addr} connected")
    connected = True
    conn.send("You are successfully connected to the server. Please respond by typing the asked details".encode(FORMAT))

    while connected:
        out = auth(conn, user, pass_user,ban)
        if out == 0:
            break

        if out==1:
            while True:
                try:
                    command = conn.recv(1024).decode(FORMAT)
                    if command == "LIST":
                        ls(conn)
                    elif command.startswith("RETR"):
                        _, filename = command.split(' ', 1)

                        retr(conn,filename.strip())
                    elif command.startswith("STOR"):
                        _, filename = command.split(' ', 1)
                        store(conn,filename)
                    elif command == "QUIT":
                        print(f"Client {addr} disconnected")
                        conn.close()
                        connected = False
                        break
                    else:
                        print("Unknown command received.")
                        break

                except Exception as e:
                    print(f"Error occurred: {e}")
                    break
        if out==2:
            while True:
                try:
                    command = conn.recv(1024).decode(FORMAT)
                    
                    if command.startswith("ADDUSER"):
                        _, username, password = command.split(' ', 2)
                        adduser(username,password,user,pass_user)
                    elif command.startswith("DELUSER"):
                        _, username = command.split(' ', 1)
                        delete(username,user,pass_user)
                    elif command.startswith("BAN"):
                        _, username = command.split(' ', 1)
                        ban(username,ban)
                    elif command.startswith("UNBAN"):
                        _, username = command.split(' ', 1)
                        unban(username,ban)
                    elif command == "QUIT":
                        print(f"Client {addr} disconnected")
                        conn.close()
                        connected = False
                        break
                    else:
                        print("Unknown command received.")
                except Exception as e:
                    print(f"Error occurred: {e}")
                    break



def auth(conn, user, pass_user,ban):
    username = conn.recv(1024).decode(FORMAT)
    passw = conn.recv(1024).decode(FORMAT)
    if (username in user) and (username not in ban):
        
        if passw == pass_user[user.index(username)]:
            if passw=="letmesleep" and username=="admin":
                conn.send("11".encode(FORMAT))
                return 2
            else:
                conn.send("10".encode(FORMAT))
                return 1
        else:
            conn.send("Invalid credentials".encode(FORMAT))
            conn.close()
            return 0
    elif ( username not in ban):
        conn.send("3".encode(FORMAT))
        res = conn.recv(1024).decode(FORMAT)
        if res == "1":
            user.append(username)
            pass_user.append(passw)
            print(user)
            print(pass_user)
            return 1
        else:
            conn.close()
            return 0
    else:
        conn.send("4".encode(FORMAT))

def ls(client):
    dirs = os.listdir("./")
    client.send("\n".join(dirs).encode())

def retr(client,path):
    client.send(path.encode())
    time.sleep(0.1)
    with open(path,'rb') as f:
        data = f.read()
        client.sendall(data)

def store(conn,path):
    stream = conn.recv(1024).decode()
    
    with open(str(path),'w') as f:
        f.write(stream)
    
    conn.send(b"File stored succesfully!")
def ban(username,ban):
    ban.append(username)

def unban(username,ban):
    ban.remove(username)

def delete(username,user,pass_user):
    i=user.index(username)
    user.remove(username)
    pass_user.pop(i)


def adduser(username,password,user,pass_user):
    user.append(username)
    pass_user.append(password)



def start():
    server.listen()
    print("Server is listening")
    user = ['admin']
    pass_user = ['letmesleep']
    ban=[]
    unban=[]

    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr, user, pass_user,ban,unban))
        thread.start()
        print(f'[Active clients]: ({threading.active_count() - 1})')

print("SERVER is starting")
start()
