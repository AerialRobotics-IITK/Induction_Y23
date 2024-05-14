import socket
import threading
import os
import tqdm
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
import hashlib
import time
import pandas as pd
port = 2002
Maximum_Connections = 20
server.bind((socket.gethostbyname(socket.gethostname()), port))


User_Pass = pd.read_csv("User_Pass.csv")
Users = list(User_Pass["Username"])
server.listen(20)
   
def USER(client, username):
    creating_user = False
    if username in Users:
                client.send("User already exists, enter Password to login".encode("utf-8"))
    else:
        Users.append(username)
        client.send("User does not exist, creating new user...\Enter a password to sign up...".encode("utf-8"))
        creating_user = True
        try:
            os.mkdir(f"User folders/{username}")
        except FileExistsError:
            pass

    return username, creating_user


def PASS(client, password,user,creating_user):
    Logged_In = False
    if creating_user:
        User_Pass.loc[len(User_Pass)] = [user,hashlib.sha256(password.encode("UTF-8")).hexdigest()]
        User_Pass.to_csv("User_Pass.csv",index=False)
        client.send("User created successfully".encode("utf-8"))
    elif hashlib.sha256(password.encode("UTF-8")).hexdigest() == User_Pass["Passwords"][User_Pass[user==User_Pass["Username"]].index[0]]:
        client.send("Login successful".encode("utf-8"))
        Logged_In = True
    else:
        client.send("Incorrect password".encode("utf-8"))
        client.send("Terminating session...".encode("utf-8"))
    return Logged_In

def LIST(client,user):
    files = os.listdir(f"User folders/{user}")
    client.send("Files in your directory are:".encode("utf-8"))
    for file in files:
        client.send(file.encode("utf-8"))

def RETR(client,user,filename):
    try:
        with open(f"User folders/{user}/{filename}","rb") as file:
            data = file.read()
            client.send(f"{len(data) }".encode("utf-8"))
            client.recv(1024)
            client.sendall(data)

    except FileNotFoundError:
        client.send("File not found".encode("utf-8"))

def STOR(client,user,filename):
    client.send("Starting upload...".encode("utf-8"))
    filesize = int(client.recv(1024).decode("utf-8"))
    # progress = tqdm.tqdm(range(filesize), f"Receiving {filename}", unit="B", unit_scale=True, unit_divisor=1024)
    recieved = 0
    with open(f"User folders/{user}/{filename}","wb") as file:
        while recieved < filesize:
            data = client.recv(1024)
            recieved += len(data)
            file.write(data)
            # print(f"Recieved {recieved} bytes out of {filesize}")
            # progress.update(len(data))
    client.send("File received successfully".encode("utf-8"))
    
            
        

def Handle_Client(client):
    user = ""
    creating_user = False
    Logged_In = False
    while True:
        request = client.recv(1024).decode("utf-8")
        print(client,request)
        if request.split(" ")[0] == "USER":
            user,creating_user = USER(client, request.split(" ")[1])
            Logged_In = False
            
            
        elif request.split(" ")[0] == "PASS":
            if user == "":
                client.send("Please enter a username first".encode("utf-8"))
            else:
                Logged_In = PASS(client, request.split(" ")[1],user,creating_user)
                creating_user = False
        elif request.split(" ")[0] == "LIST":
            LIST(client,user)
        elif request.split(" ")[0] == "RETR":
            if Logged_In:
                if request.split(" ")[1]=="":
                    client.send("Please enter a filename".encode("utf-8"))
                else:
                    RETR(client,user,request.split(" ")[1])
            else:
                client.send("Please Login first".encode("utf-8"))
        elif request.split(" ")[0] == "STOR":
            if request.split(" ")[1]=="":
                client.send("Please enter a filename".encode("utf-8"))
            elif Logged_In:
                if request.split(" ")[1] in os.listdir(f"User folders/{user}"):
                    client.send("File already exists, do you want to overwrite?".encode("utf-8"))
                    reply = client.recv(1024).decode("utf-8")
                    if reply == "N":
                        client.send("Cancelling operation...".encode("utf-8"))
                    else:
                        STOR(client,user,request.split(" ")[1])
                else:
                    print("Creating new file")
                    client.send("Starting upload.".encode("utf-8"))
                    client.recv(1024)
                    STOR(client,user,request.split(" ")[1])
            else:
                client.send("Please Login first".encode("utf-8"))
        else:
            client.send("Invalid command".encode("utf-8"))
            continue


print("Server started at {}",time.ctime())
while True:
    client, address = server.accept()
    print(f"Connection received from {address} at {time.ctime()}")
    client_handler = threading.Thread(target=Handle_Client, args=(client,))
    client_handler.start()
