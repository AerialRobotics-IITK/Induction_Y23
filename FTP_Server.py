import socket
import threading
import os
import sys
import time
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

server.bind((IP_ADDR,port))

print(f"Server is listening on {IP_ADDR}:{port}")

clients = []
usernames = {}
ban_usernames = {}
server.listen()
usernames["asd"] = "asd" 

def add_user(username,password):
    usernames[username] = password
    
def del_user(username):
    del usernames[username]        

def ban_user(username):
    ban_usernames[username] =usernames[username]
    del usernames[username]
    
def unban_user(username):
    usernames[username] = ban_usernames[username]
    del ban_usernames[username]
    
       
def admin_access(client):
    client.send("PASSWORD?".encode())
    admin_password = client.recv(1024).decode()
    if(admin_password=='AERIAL'):
        print(f"Admin is successfully logged in.")
        client.send("Successfully logged in as ADMIN".encode())
        while True:
            client.recv(1024).decode()
            client.send("option?".encode())
            option = client.recv(1024).decode()
            if option == "ADDUSER":
                client.send("username?".encode())
                username=client.recv(1024).decode()
                if(username in usernames):
                    client.send("Username already registered".encode())
                    continue
                client.send("password?".encode())
                password =client.recv(1024).decode()
                add_user(username,password)
                client.send("Username successfully registered".encode())
            elif option == "DELUSER":
                client.send("username?".encode())
                username=client.recv(1024).decode()
                if(username in usernames):
                    del_user(username)
                    client.send("Username successfully deregistered".encode())
                else:
                    client.send("No such username exist".encode())
            elif option == "BANUSER":
                client.send("username?".encode())
                username=client.recv(1024).decode()
                if(username in usernames):
                    ban_user(username)
                    client.send("Username successfully banned".encode())
                else:
                    client.send("No such username exist".encode())  
            elif option == "UNBANUSER":
                client.send("username?".encode())
                username=client.recv(1024).decode()
                if(username in ban_usernames):
                    unban_user(username)
                    client.send("Username successfully unbanned".encode())
                else:
                    client.send("No such username exist".encode())  
            else:
                continue
    else:
        client.send("Wrong password".encode())
        
def list(client):
    listing = os.listdir(os.getcwd())
    client.send(str(len(listing)).encode())
    
    for i in listing:
        file_size = os.path.getsize(i)
        client.send(i.encode())
        client.recv(1024).decode()
        client.send(str(file_size).encode())
        client.recv(1024).decode()
        
def retr(client):
    file_name = client.recv(1024).decode()
    listing = os.listdir(os.getcwd())
    if file_name in listing:
        client.send("File found successfully".encode())
        file_size = os.path.getsize(file_name)
        client.sendall(file_size.to_bytes(4, byteorder='big'))
        with open(file_name, 'rb') as file:
            file_data = file.read()
            client.sendall(file_data)
        print("File sent successfully.")
    else:
        client.send("File does not exist".encode())
        print("File not found.")

def upld(client):
    file_exists = client.recv(1024).decode()
    if file_exists == "File exists":
        file_size_bytes = client.recv(4)
        file_name = client.recv(1024).decode()
        file_size = int.from_bytes(file_size_bytes, byteorder='big')
        file_data = b''
        while len(file_data) < file_size:
            chunk = client.recv(1024)
            if not chunk:
                break
            file_data += chunk
        with open(file_name, 'wb') as file:
            file.write(file_data)
        print("File uploaded successfully.")
    else:
        print("File does not exist.")        
        
        
    
"""
def upld(client):
    message = client.recv(1024).decode()
    if(message=="File not found"):
        return
    file_size_bytes = client.recv(4)
    file_name = client.recv(1024).decode()
    file_size = int.from_bytes(file_size_bytes, byteorder='big')
    file_data = b''
    while len(file_data) < file_size:
        chunk = client.recv(102400)
        if not chunk:
            break
        file_data += chunk
        print(f"{file_size}   {len(file_data)}")
    print(f"Uploaded")
    with open(file_name, 'wb') as file:
        file.write(file_data)
    file.close()
    
    
def retr(client):
    file_name = client.recv(1024).decode()
    listing = os.listdir(os.getcwd())
    if(file_name in listing):
        client.send("File found successfully".encode())
    else:
        client.send("File does not exist".encode())
        return    
    file = open(file_name,"rb")
    data = file.read()
    client.sendall(len(data).to_bytes(4, byteorder='big'))
    file.close()
    client.sendall(data) 
"""    
    
 
def client_access(client,username):
    client.send("PASSWORD?".encode())
    password = client.recv(1024).decode()
    if(password == usernames[username]):
        print(f"\n{username} succesfully logged in") 
        client.send("{username} successfully logged in".encode())
        while True:
            client.send("option?".encode())
            option = client.recv(1024).decode()
            if(option=="LIST"):
                list(client)
            elif(option=="UPLD"):
                upld(client)
            elif(option=="RETR"):
                retr(client)
                
                
    
    else:
        client.send("Wrong password".encode())    
    
def accept_client():
    while True:
        client, address = server.accept()
        print(f"\nConnection received from {address}")
        while True:
            client.send("USERNAME?".encode())
            admin_user = client.recv(1024).decode()    
            if(admin_user=="ADMIN"):
                accepting_client = threading.Thread(target = accept_client)
                accepting_client.start()
                admin_access(client)
            elif(admin_user in usernames):
                accepting_client = threading.Thread(target = accept_client)
                accepting_client.start()
                client_access(client,admin_user)               
            elif(admin_user in ban_usernames):
                client.send("User is Banned!".encode())                
            else:
                client.send("Sorry you are not registered by admin".encode())
                   

accept_client()


  
        
   



















