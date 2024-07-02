import socket
import threading

username = input("Enter your username : ")
host_name = socket.gethostname()

client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(host_name)

PORT = 5050

client.connect((IP_ADDR,PORT))
ch = input("Enter c if you are client and a if you are admin")
if ch == 'c':
    while True:
        message_1 = client.recv(1024).decode()

        # while True:
        if message_1 == "Enter your username":
                client.send(username.encode())
                message_2 = client.recv(1024).decode()
                if message_2 == "You are a new user please enter a password for making an account":
                    password = input("Enter your password")
                    client.send(password.encode())
                elif message_2 == "You are an existing user, to proceed kindly enter your password":
                    password = input("Enter you password")
                    client.send(password.encode())
                    message_3 = client.recv(1024).decode()
                    if message_3 == "You have been successfully logged in":
                        cmd = input(("Enter the command you want to execute : LIST for listing all the files in the directory,RETR for retrieving a file already stored in a directory,SEND for sending a file to all clients,QUIT"))
                        client.send(cmd.encode())
                    else: print("Your connection has been closed from the server side")
        else :
                break
# elif ch == 'a':
    # cmd = input("Enter ")
    
    
        
    client.close()
                
            