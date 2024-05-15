import socket
import os
import threading

server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

IP=socket.gethostbyname(socket.gethostname())
port=9999

server.bind((IP,9999))

server.listen()
print("Server is listening from {} at port {}".format(IP,9999))


users=dict()                                       #dictionary containing username mapped to password
clients=[]                                          

cwd=os.getcwd()

def USER(username):
    if username in ban:
        return 1
    elif username in users:
        return 2
    else:
        return 0


def PASS(username,password):
    for k,v in users.values():
        if (k,v)==(username,password):
            return True
    return False
           
def LIST():
    current_directory = os.getcwd()
    files=os.listdir(current_directory)
    msg=''
    for file in files:
        msg=msg+file+'\n'
    client.send(msg.encode())
    print(f"\nListed files for {client}")

def RETR(filename):
    files=os.listdir(cwd)
    if filename not in files:
        client.send("\nFile not found".encode())
    else:
        client.send("\nFile found".encode())
        file=open(filename,"rb")
        data=file.read(1024)
        while data:
            client.send(data)
            data=file.read(1024)
        client.send(b"<END>")
        print(f"\nFile {filename} sent to {client}")

def STOR(filename):
    files=os.listdir(cwd)
    if filename in files:
        client.send("\nFile with that name already exists")
    else:
        file=open(filename,'wb')
        data=client.recv(1024)
        while data!="<END>":
            file.write(data)
            data=client.recv(1024)
        print(f"Received file {filename} from {client}")

def QUIT():
    clients.remove(client)
    client.close()

def ADDUSER(username,password):
    users[username]=password

def REMOVEUSER(username):
    users.pop(username)

ban=[]

def BAN(username):
    if username in users:
        users.pop(username)
    ban.append(username)

def UNBAN(username):
    if username in ban:
        ban.remove(username)

def handle_client(client):
    while True:
        try:
            client.send('''\nWhat would you like to do?
1. List all files
2. Retrieve a file from the server
3. Store a file on the server
4. Exit the server
Enter the option number: '''.encode())
            op=client.recv(1024).decode()
            if op=="1":
                LIST()
            elif op=="2":
                client.send("\nEnter the file name: ")
                filename=client.recv(1024).decode()
                RETR(filename)
            elif op=="3":
                client.send("\nEnter the file name: ")
                filename=client.recv(1024).decode()
                STOR(filename)
            elif op=="4":
                QUIT()
        except:
            clients.pop()
            client.close()
            print(f"Active Connection : {threading.active_count()}")
            break

if __name__ == "__main__":
    while True:
        client,address=server.accept()
        print("Connection received from {}".format(address))
        while True:
            client.send("Enter your Username: ".encode())
            username=client.recv(1024).decode()
            if USER(username)==2:
                print("reached here")
                client.send("Enter your Password to login: ".encode())
                password=client.recv(1024).decode()
                if PASS(username,password):
                    client.send("Successfully connected to the server".encode())
                    clients.append(client)
                    t = threading.Thread(target=handle_client, args=(client,))
                    t.start()
                    print(f"Active Connection : {threading.active_count()}")
                else:
                    client.send("Password incorrect".encode())
                    client.close()
                break
            elif USER(username)==0:
                client.send("Enter a password to register: ".encode())
                password=client.recv(1024).decode()
                users[username]=password
                client.send("Registered succesfully\n".encode())
                print(f"User {username} registered")
            elif USER(username)==1:
                client.send("You have been banned from this server".encode())
                client.close()
                break






