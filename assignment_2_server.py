import socket
import threading
import os
server_1 = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

host_name = socket.gethostname()
PORT = 5050
IP_ADDR = socket.gethostbyname(host_name)

server_1.bind((IP_ADDR,PORT))
server_1.listen()

print(f"server has started listening {IP_ADDR} : {PORT}")
clients = []
usernames = []
passwords = []

directory = "assignment_2"
parent_directory = "C:/"
new_dir = os.path.join(parent_directory,directory)
try:
    os.makedirs(new_dir,exist_ok=True)
    print("The directory has been successfully created")
except OSError as error:
    print("There has been an error in creating the directory")
    

def new_client():
    while True:
        client ,address = server_1.accept()
        
        if client in clients:
            client.send("Enter a username".encode())
            while True:
                username = client.recv(1024).decode()
                if username not in usernames:
                    client.send((f"You are an existing user, to proceed kindly enter your password").encode())
                    password_recv = client.recv(1024).decode()
                    if(password_recv == passwords[username]):
                        # broadcast
                        client.send(f"You have been successfully logged in").encode()
                        thread_client = threading.Thread(target = handle_client,args = (client, ))
                        thread_client.start()
                    else : client.send(("The entered password is wrong :(\nCLosing your connection").encode())
                    client.close()
        else :
                    client.send(("You are a new user please enter a password for making an account").encode())
                    password = client.recv(1024).decode()
                    clients.append(client)
                    usernames[client] = username
                    passwords[username] = password
                    client.send((f"You have been successfully connected to the server\n with user credentials -> username : {usernames[client]}\n password : {passwords[username]}").encode())
                    thread_client = threading.Thread(target = handle_client,args = (client, ))
                    thread_client.start()
        # elif 
                    
def handle_client(client):
    while True :
             message_from_client = client.recv(1024).decode()
             if message_from_client == "LIST":
                 #searched about this method of searching files with the help of os library
                 client.send(os.listdir(new_dir))
                 
             elif message_from_client == "RETR":
                 client.send((RETR_FILE().encode()))
                 print(f"\n{client} retrieved data from a file")
             elif message_from_client == "STOR":
                 STOR_FILE(client)
             elif message_from_client == "QUIT":
                  client.close()


i = 0

def broadcast(message):
           for client in clients:
                client.send(message.encode())
def RETR_FILE():
            file_path = input("enter the path to file you want to retrieve")
            try:
                file_obj = open(file_path,"rb")
                file_content = file_obj.read()
                
                return file_content
            
            except FileNotFoundError:
                return "Requested file does not exist in the directory"
        
def STOR_FILE(client):
    file_path = input("enter the path to file you want to store in the directory")
    file_obj = open(file_path,"rb")
    file_content = file_obj.read()
    global i 
    new_file_name = f"file_{i}.txt"
    i += 1
    
    file_path = new_dir + new_file_name
    with open(file_path,'wb') as file:
        try:
            file.write(file_content)
            msg_to_all = f"client {client} just added {new_file_name} to the directory : {new_dir}"
            broadcast(msg_to_all)
        except OSError as error:
            print(f"There has been some error : {error}")
            

if __name__ == "__main__":
    new_client()
    
    
    

        
        