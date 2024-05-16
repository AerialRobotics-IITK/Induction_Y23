import socket
import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

client.connect((IP_ADDR,port))

while True:
    username = input("Enter username : ")
    if(username!="ADMIN"):
        print(f"\nWrong username,Try again!")
    else:
        break

while True:
    message = client.recv(1024).decode()
    if message == "USERNAME?":
        client.send(username.encode())
    message = client.recv(1024).decode()
    if message == "PASSWORD?":
        password = input("Enter password : ")
        client.send(password.encode())
    message = client.recv(1024).decode()
    if message == "Wrong password":
        print(f"\n{message}")
        continue
    else:
        print(f"\n{message}")
        while True:
            option = input(f"\nSelect command\n1.ADDUSER = add new user\n2.DELUSER = delete a user\n3.BANUSER = ban a user\n4.UNBANUSER = unban a user")
            client.send("match".encode())
            message = client.recv(1024).decode()
            client.send(option.encode())
            if(message=="option?"):
                if(option=="ADDUSER" or option=="DELUSER" or option=="BANUSER" or option=="UNBANUSER"):
                    if(option=="ADDUSER"):
                        message = client.recv(1024).decode()
                        username_ = input(f"Enter username")
                        client.send(username_.encode())
                        message = client.recv(1024).decode()
                        if(message=="password?"):
                            password_= input(f"Enter password")
                            client.send(password_.encode())
                            message = client.recv(1024).decode()
                            print(f"\n{message}")
                        else:
                            print(f"\n{message}")    
                    else:
                        message = client.recv(1024).decode()
                        username_ = input(f"Enter username")
                        client.send(username_.encode())
                        message = client.recv(1024).decode()
                        print(f"\n{message}") 
                else:
                    print(f"\n Wrong input, Try Again!")
            
        
