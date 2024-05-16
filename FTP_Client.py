import socket
import threading
import os

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

client.connect((IP_ADDR,port))

def list():
    no_of_files = client.recv(1024).decode()
    print("FILE NAME\t FILE SIZE\n")
    for i in range(int(no_of_files)):
        message = client.recv(1024).decode()
        print(f"{message}\t")
        client.send(" ".encode())
        message = client.recv(1024).decode()
        print(f"{message}\n")
        client.send(" ".encode())

def retr():
    file_name = input("\nEnter file name:")
    client.send(file_name.encode())
    file_size = client.recv(1024).decode()
    file = open(file_name,"wb")
    file_bytes =b""
    done = False
    
    while not done:
        data = client.recv(1024)
        if file_bytes[-5:] == b"<END>":
            done = True
        else:
            file_bytes += data
            
    file.write(file_bytes)
    file.close()

def upld():
    file_name = input("\nEnter file name:")
    file = open(file_name,"rb")
    file_size = os.path.getsize(file_name)
    client.send(file_name.encode())
    client.send(str(file_size).encode())
    data = file.read()
    client.sendall(data)
    client.send(b"<END>")   
    file.close()  

while True:
    username = input("Enter username : ")
    if(username=="ADMIN"):
        print(f"\nYou don't have admin access.\nOnly log in as a user is available.")
        continue
    message = client.recv(1024).decode()
    if message == "USERNAME?":
        client.send(username.encode())
    message = client.recv(1024).decode()
    if message == "PASSWORD?":
        password = input("Enter password : ")
        client.send(password.encode())
        message = client.recv(1024).decode()
        print(f"\n{message}")
        if(message=="Wrong password"):
            continue
        print(f"\nEnter command\n1.LIST = show list of files\n2.RETR = to retrive a file\n3.STOR = to store a file\n4.QUIT")
        while True:
            message = client.recv(1024).decode()
            while True:
                option = input("\n")
                if(option=="QUIT"):
                    client.close()
                if(option!="LIST" and option != "RETR" and option != "UPLD"):
                    print(f"\nNo such command available")
                    continue
                client.send(option.encode())
                if(option=="LIST"):
                    list()
                    break
                elif(option=="RETR"):
                    retr()
                    break
                elif(option=="UPLD"):
                    upld()
                    break
                    
                        
                    
    else:
        print(f"\n{message}")    
