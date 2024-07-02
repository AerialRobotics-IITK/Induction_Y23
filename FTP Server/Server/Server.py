import socket
import threading
import os
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
import hashlib
import time
import pandas as pd
import shutil
port = 2000
server.bind((socket.gethostbyname(socket.gethostname()), port))
# ADDING FILE TO LOG-->
LOG = open("SERVER_LOG.txt","a")
User_Pass = pd.read_csv("User_Pass.csv")
Users = list(User_Pass["Username"])
server.listen(20)
   
def USER(client, username):
    creating_user = False
    banned = False

    if username in Users:
        if User_Pass["Ban/Unban"][Users.index(username)] == 1:
            banned = True
            client.send("User is banned, please contact admin".encode("utf-8"))
        else:
            client.send("User already exists, enter Password to login".encode("utf-8"))
    else:
        Users.append(username)
        client.send("User does not exist, creating new user...\nEnter a password to sign up...".encode("utf-8"))
        creating_user = True
        try:
            os.mkdir(f"User folders/{username}")
        except FileExistsError:
            pass

    return username, creating_user,banned


def PASS(client, password,user,creating_user):
    Logged_In = False
    if creating_user:
        User_Pass.loc[len(User_Pass)] = [user,hashlib.sha256(password.encode("UTF-8")).hexdigest(),0]
        User_Pass.to_csv("User_Pass.csv",index=False)
        client.send("User created successfully".encode("utf-8"))
    elif hashlib.sha256(password.encode("UTF-8")).hexdigest() == User_Pass["Passwords"][User_Pass[user==User_Pass["Username"]].index[0]]:
        client.send("Login successful".encode("utf-8"))
        Logged_In = True
    else:
        client.send("Incorrect password".encode("utf-8"))
    return Logged_In

def LIST(client,user):
    files = os.listdir(f"User folders/{user}")
    client.send("Files in your directory are:\n".encode("utf-8"))
    for file in files:
        client.send(f"{file}\n".encode("utf-8"))

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
    received = 0
    with open(f"User folders/{user}/{filename}","wb") as file:
        while received < filesize:
            data = client.recv(1024)
            received += len(data)
            file.write(data)
            # print(f"Received {received} bytes out of {filesize}")
            # progress.update(len(data))
    client.send("File received successfully".encode("utf-8"))
    
            
        

def Handle_Client(client):
    user = "<NOT LOGGED IN>"
    banned = False
    creating_user = False
    Logged_In = False
    while True:
        try:
            request = client.recv(1024).decode("utf-8")
            if request == "<NOT LOGGED IN>":
                print(f"{time.ctime()} :Connection closed unexpectedly for {user} on {address[0]}:{address[1]}\n")
                LOG.write(f"{time.ctime()} :Connection closed unexpectedly for {user} on {address[0]}:{address[1]}\n")
                client.close()
                break
            else:
                print(f"At {time.ctime()}:{request} by {user} on {address[0]}:{address[1]}")
            LOG.write(f"At {time.ctime()}:{request} by {user} on {address[0]}:{address[1]}\n")
            if request.split(" ")[0] == "QUIT":
                client.send("Terminating session...".encode("utf-8"))
                client.close()#Close the connection
                break
            elif request.split(" ")[0] == "USER":
                try:
                    user,creating_user,banned = USER(client, request.split(" ")[1])
                    if banned:
                        user = "<NOT LOGGED IN>"
                    Logged_In = False
                except :
                    client.send("Please enter a username".encode("utf-8"))
                
                
            elif request.split(" ")[0] == "PASS":
                try:
                    if user == "<NOT LOGGED IN>":
                        client.send("Please enter a username first".encode("utf-8"))
                    else:
                        Logged_In = PASS(client, request.split(" ")[1],user,creating_user)
                        creating_user = False
                except:
                    client.send("Please enter a password".encode("utf-8"))
            elif request.split(" ")[0] == "LIST":
                LIST(client,user)
            elif request.split(" ")[0] == "RETR":
                try:
                    if Logged_In:
                        if request.split(" ")[1]=="<NOT LOGGED IN>":
                            client.send("Please enter a filename".encode("utf-8"))
                        else:
                            RETR(client,user,request.split(" ")[1])
                    else:
                        client.send("Please Login first".encode("utf-8"))
                except:
                    client.send("Please enter a filename to retrieve".encode("utf-8"))
            elif request.split(" ")[0] == "STOR":
                try:
                    if request.split(" ")[1]=="":
                        client.send("Please enter a filename".encode("utf-8"))
                    elif Logged_In:
                        if request.split(" ")[2] in os.listdir(f"User folders/{user}"):
                            client.send("File already exists, do you want to overwrite?".encode("utf-8"))
                            reply = client.recv(1024).decode("utf-8")
                            if reply == "N":
                                client.send("Cancelling operation...".encode("utf-8"))
                            else:
                                STOR(client,user,request.split(" ")[1])
                        else:
                            # LOG.write("Creating new file\n")
                            client.send("Starting upload.".encode("utf-8"))
                            client.recv(1024)
                            STOR(client,user,request.split(" ")[2])
                    else:
                        client.send("Please Login first".encode("utf-8"))
                except:
                    client.send("Please enter a filename to store".encode("utf-8"))
            elif request.split(" ")[0] == "ADDUSER":
                try:
                    if user == "ADMIN":
                        print("User = ",request.split(" ")[1], "Password = ",request.split(" ")[2])
                        if Logged_In:
                            print("done")
                            _,creating_user,_ = USER(client, request.split(" ")[1])
                            if creating_user:
                                print("done")
                                PASS(client, request.split(" ")[2],user,creating_user)
                                print("done")
                        else:
                            client.send("Please Login first".encode("utf-8"))
                    else :
                        client.send("You do not have permission to add users".encode("utf-8"))
                except Exception as e:
                    client.send(e.encode("utf-8"))
                    client.send("Please enter a username and password".encode("utf-8"))
            elif request.split(" ")[0] == "DELUSER":
                if user == "ADMIN":
                    if Logged_In:
                        print(request.split(" ")[1],request.split(" ")[1] in Users,Users)
                        if request.split(" ")[1] in Users:
                            # print('done')
                            try:
                                os.rmdir(f"User folders/{request.split(' ')[1]}")
                            except Exception as e:
                                client.send("User directory not empty, do you want to delete anyway?".encode("utf-8"))
                                reply = client.recv(1024).decode("utf-8")
                                if reply == "N":
                                    client.send("Cancelling operation...".encode("utf-8"))
                                    continue
                                else:
                                    shutil.rmtree(f"User folders/{request.split(' ')[1]}")

                            # print('done')
                            # User_Pass_copy = User_Pass.copy()

                            User_Pass.drop(Users.index(request.split(" ")[1]),inplace=True)
                            Users.remove(request.split(" ")[1])
                            # print('done')
                            User_Pass.to_csv("User_Pass.csv",index=False)
                            # print('done')
                            client.send("User deleted successfully".encode("utf-8"))
                        else:
                            client.send("User does not exist".encode("utf-8"))
                    else:
                        client.send("Please Login first".encode("utf-8"))
                else:
                    client.send("You do not have permission to delete users".encode("utf-8"))
                # except Exception as e:
                #     client.send(e.encode("utf-8"))
                #     client.send("Please enter a username to delete".encode("utf-8"))
            elif request.split(" ")[0] == "BAN":
                try:
                    if user == "ADMIN":
                        if Logged_In:
                            if Users.index(request.split(" ")[1]) != -1:
                                User_Pass["Ban/Unban"][Users.index(request.split(" ")[1])] = 1
                                User_Pass.to_csv("User_Pass.csv",index=False)
                                client.send("User banned successfully".encode("utf-8"))
                            else:
                                client.send("User does not exist".encode("utf-8"))
                        else:
                            client.send("Please Login first".encode("utf-8"))
                    else:
                        client.send("You do not have permission to ban users".encode("utf-8"))
                except:
                    client.send("Please enter a username to ban".encode("utf-8"))
            elif request.split(" ")[0] == "UNBAN":
                try:
                    if user == "ADMIN":
                        if Logged_In:
                            if Users.index(request.split(" ")[1]) != -1:
                                User_Pass["Ban/Unban"][Users.index(request.split(" ")[1])] = 0
                                User_Pass.to_csv("User_Pass.csv",index=False)
                                client.send("User unbanned successfully".encode("utf-8"))
                            else:
                                client.send("User does not exist".encode("utf-8"))
                        else:
                            client.send("Please Login first".encode("utf-8"))
                    else:
                        client.send("You do not have permission to unban users".encode("utf-8"))
                except:
                    client.send("Please enter a username to unban".encode("utf-8"))
            else:
                client.send("Invalid command".encode("utf-8"))
                continue
        except :
            LOG.write(f"{time.ctime()} :Connection closed unexpectedly for {user} on {address[0]}:{address[1]}\n at ")
            break


print(f"Server started at {time.ctime()}")
LOG.write(f"Server started at {time.ctime()}\n")
while True:
    client, address = server.accept()
    print(f"Connection received from {address[0]}:{address[1]} at {time.ctime()}")
    LOG.write(f"Connection received from {address[0]}:{address[1]} at {time.ctime()}\n")
    client_handler = threading.Thread(target=Handle_Client, args=(client,))
    client_handler.start()