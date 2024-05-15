import socket
import threading
import os
from pathlib import Path
import struct
import sys


# Create a socket object for the server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 5050
BUFFER_SIZE = 1024 
# Bind the server to listen on port 1234
server.bind((IP_ADDR,port))

# Start listening for incoming connections
server.listen()

# Print a message indicating that the server is listening
print(f"Server is listening on {IP_ADDR}:{port}")
print("Hello")

# Making List of users registered
users = ["sanyam"]
usernames = []
passwords = []

client, addr = server.accept()
print( "\nConnected to by address: {}".format(addr))




def list_files():
    print ("Listing files...")
    # Get list of files in directory
    listing = os.listdir(os.getcwd())
    # Send over the number of files, so the client knows what to expect (and avoid some errors)
    client.send(struct.pack("i", len(listing)))
    total_directory_size = 0
    # Send over the file names and sizes whilst totaling the directory size
    for i in listing:
        # File name size
        client.send(struct.pack("i", sys.getsizeof(i)))
        # File name
        client.send(i)
        # File content size
        client.send(struct.pack("i", os.path.getsize(i)))
        total_directory_size += os.path.getsize(i)
        # Make sure that the client and server are syncronised
        client.recv(BUFFER_SIZE)
    # Sum of file sizes in directory
    client.send(struct.pack("i", total_directory_size))
    #Final check
    client.recv(BUFFER_SIZE)
    print ("Successfully sent file listing")
    return


def quit():
    # Send quit conformation
    client.send("1")
    # Close and restart the server
    client.close()
    server.close()
    os.execl(sys.executable, sys.executable, *sys.argv)
    


def new_client(): 
    print("Code started")
    client.send("Enter a username".encode())
    while True:
      username = client.recv(1024).decode()
      if username in usernames:
        client.send(("You are an existing user, pls enter password").encode())
        password_recv = client.recv(1024).decode()
        if(password_recv == passwords[username]):
                # broadcast
                client.send("Logged in.. Congratulations").encode()
                thread_client = threading.Thread(target = handle_client,args = (client, ))
                thread_client.start()
        else:
             client.send(("Wrong Password").encode())
             client.close()
                    
      else : 
            client.send(("You are a new user. Please enter a password ").encode())
            password = client.recv(1024).decode()
            users.append(client)
            usernames[client] = username
            passwords[username] = password
            client.send((f"You have been successfully connected to the server\n with user credentials -> username : {usernames[client]}\n password : {passwords[username]}").encode())
            thread_client = threading.Thread(target = handle_client,args = (client, ))
            thread_client.start()
            break




def retrive():
    print("Enter file path you want to retrive")
    path = input()
    obj = open(path,"rb")
    content = obj.read()
                
    return content









     



def handle_client(client):

    while True :
             rec = client.recv(1024).decode()
             if rec == "L":
                 list_files()
             if rec == 'Q':
                   quit()
             if rec == 'R':
                  retrive()
             if rec== 'S':
                  break
                  
                  

                 

new_client()        


