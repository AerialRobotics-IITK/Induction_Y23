import socket
import threading
import os
import time

USERS={}
BAN=[]
A_UNAME= "admin"
A_PASSWORD="123"
HOST = socket.gethostbyname(socket.gethostname())
#HOST = "192.168.1.3"
PORT=6968

def getlist(client):
    l=''
    for i in os.listdir():
        l+=str(i)+'+'
    client.send(l.encode())
    return
def retr(client):
    file_name = client.recv(1024).decode()
    if not os.path.exists(file_name):
        client.send("0".encode())
        print(f"\nFile '{file_name}' does not exist on server.")
        return
    try:
        client.send("1".encode())
        print("\n****sent1****\n")
        with open(file_name, 'rb') as file:
            data = file.read()
            client.sendall(data)
            client.send(b"<KHTM>")
        print(f"File '{file_name}' given to client successfully!")
    except socket.error:
        print(f"Error uploading file: {file_name}")
def stor(client):
    file_name = client.recv(1024).decode()
    try:
        with open(file_name, 'wb') as file:
            file_bytes = b''
            while True:
                if file_bytes.endswith(b"<KHTM>"): 
                    break
                data = client.recv(1024)
                file_bytes += data
            file_bytes=file_bytes[:-6]
            file.write(file_bytes)
    except socket.error:
        print("Error receiving file:", file_name)


def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST,PORT))
    server.listen()
    print(f"Server is listening on {HOST}, Port: {PORT}\n\n Connect clients!\n\n\n")
    aunthenticate_client(server)
def aunthenticate_client(server):
    while True:
        client, address = server.accept()
        print(f"\nConnection received from {address}")

        while True:
            #Ask for username and password
            client.send("uname?".encode())
            uname = client.recv(1024).decode()
            client.send("passwd?".encode())
            passwd = client.recv(1024).decode()
            if (uname in list(USERS.keys())) and (passwd in list(USERS.values())):
                if uname in BAN:
                    client.send("BAN".encode())
                    return
                client.send("connected".encode())
                t = threading.Thread(target=handle_client, args=(client,))
                t.start()
                break
            elif ((uname in USERS.keys) and (passwd not in USERS.values)):
                client.send("incorrect".encode())
                continue
            else:
                client.send("notuser".encode())
                client.close()
                break
def handle_client(client):
    while True:
        ch=client.recv(1024).decode()
        print("\n**received: ",end='')
        if ch=='1' :
            print(ch)
            getlist(client)
        elif ch=='2' :
            print(ch)
            retr(client)
        elif ch=='3':
            print(ch)
            stor(client)
        elif ch=='4':
            print(ch)
            client.close()
            print("connection closed with",client)
            return

def main():
    #ADMIN CONTROLS
    authentcated=False
    while True:
        if not authentcated:
            un=input("\n\nEnter Admin username : ")
            psd=input("Enter Admin password: ")
        if un==A_UNAME and psd==A_PASSWORD :
            c=int(input("\n\n\n****Admin Login Successful****\n\nPress 1 to ADD USER\nPress 2 to DEL USER\nPress 3 to BAN USER\nPress 4 to UNBAN USER: \nPress 5 to Start Server\n"))
            authentcated=True
            if c==1:
                print("\n\nAdd user\n\n")
                user_un=input("Enter username : ")
                user_psd=input("Enter password: ")
                USERS[user_un]=user_psd
                print(user_un,"Added")
                continue
            if c==2:
                print("\n\nDelete user\n\nList of Users:")
                for i in USERS:
                    print(i)
                print("\n")
                user_un=input("Enter username : ")
                del USERS[user_un]
                print(user_un,"Deleted")
                continue
            if c==3:
                print("\n\nBan user\n\nList of Users:")
                for i in USERS:
                    print(i)
                print("\n")
                user_un=input("Enter username : ")
                BAN.append(user_un)
                print(user_un,"Banned")
                continue
            if c==4:
                print("\n\nUnban user\n\nList of Banned Users:")
                print(BAN,"\n")
                print("\n")
                user_un=input("Enter username : ")
                BAN.remove(user_un)
                print(user_un,"Unbanned")
                continue
            if c==5:
                start_server()
                break
            else :
                continue
        else :
                print("\nIncorrect credentials!!\n")


main()


