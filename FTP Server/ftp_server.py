import socket
import sqlite3
import threading
import os


# def connect_db():
#     con = sqlite3.connect('tutorial.db')
#     con.execute("CREATE TABLE IF NOT EXISTS users (id )")
    

server  = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

server.bind((IP_ADDR, port))
server.listen()


# storing users as 
users = {}
logged_in_sessions = []


clients = []

def broadcast(message, sender_client):
    for client in clients:
        if client != sender_client:
            client.send(message.encode('utf-8'))


def send_file(filename: str,file_bytes: bytearray, client: socket):
    #client.send("F".encode())
    #client.recv(1024)
    filename+="b"
    bytes_size = len(file_bytes).to_bytes(8)
    filename_size = len(filename.encode()).to_bytes(8)
    print("Sending file size:", bytes_size)
    client.send(bytes_size)
    print("Sending filename size:", filename_size)
    client.send(filename_size)
    client.send(filename.encode())
    client.sendall(file_bytes)


def receive_file(client):
    filename_size = int.from_bytes(client.recv(8))
    filename = client.recv(filename_size)
    data_size = int.from_bytes(client.recv(8))
    received_data_size = 0
    with open(filename, "wb") as f:
        while received_data_size < data_size:
            chunk = client.recv(data_size-received_data_size)
            if not chunk:
                break
            received_data_size += len(chunk)
            f.write(chunk)
        f.close()
            

        




def client_listener():
    while True:
        client, address = server.accept()
        client.send("USERNAME?".encode())
        nickname = client.recv(1024).decode()
        client.send(f"Welcome , {nickname}".encode())
        filebytes = b''
        with open("test.md", "rb") as f:
            filebytes += f.read()
        receive_file(client)
        #send_file("test.md", filebytes, client)
        t = threading.Thread(target=handle_client, args=(client,))
        t.start()

def handle_authenticated_user(username, client):
    client.send("Successfuly logged in! You can now use the FTP Server")
    while True:
        try:
            message = client.recv(1024).decode()
            if(len(message) > 4):
                message_token = message[:4]
                if(message_token.upper() == "LIST"):
                    list_files = ""
                    for i in os.popen("ls -p | grep -v /").read():
                        head, tail = os.path.split(i)
                        list_files = list_files + tail + "\n"
                    client.send((1).to_bytes(4)) # to inform command was parsed
                    client.send(len(list_files).to_bytes(8))
                    client.sendall(list_files)
                        #list_files.append(tail)
                elif(message_token.upper() == "RETR"):
                    filename = message_token[5:]
                    fff = False
                    for i in os.popen("ls -p | grep -v /").read():
                        head, tail = os.path.split(i)
                        if(filename == tail):
                            fff = True
                            break
                    if(fff):
                        client.send((2).to_bytes(4)) # to inform command was parsed
                        send_file(filename, client)
                        print("Returned here")
                    else:
                        client.send((3).to_bytes(4)) # failed to find file
                        client.send("Failed to find file. Please ensure file name is correct")
                elif(message_token.upper() == "STOR"):
                    filename = message_token[5:]
                    fff = False
                    for i in os.popen("ls -p | grep -v /").read():
                        head, tail = os.path.split(i)
                        if(filename == tail):
                            fff = True
                            break
                    if(not fff):
                        client.send((4).to_bytes(4)) # to inform command was parsed
                        receive_file(client)
                        print("Returned here")
                    else:
                        client.send((5).to_bytes(4)) # failed to find file
                        client.send("File already exists. Please rename before uploading")
                elif(message_token.upper() == "QUIT")
                    
                    
        

            
        except:
            clients.remove(clients.index(client))
            client.close()
            if(users[username][0] == 3):
                users[username][0] = 0
            
            
            
    

def handle_client(client):
    while True:
        try:
            # Receive a message from the client
            client.send("Please use the command USER [username] to login")
            message = client.recv(1024).decode()
            auth_failure = False
            # Broadcast the message to all other clients
            if(len(message) < 4):
                auth_failure = True
            else:    
                message_token = message
                if(message[:4] == "USER"):
                    username = message[5:]

                    if username in users.keys():
                        client.send((20).to_bytes())
                        client.send("Please enter the password in the format: PASS [pwd]")
                        message = client.recv(1024).decode()
                        if len(message)> 5 and message[:4] == "PASS":
                            password = message[5:]
                            if(username[users][1] == password):
                                if(username[users][0] == 0): # is not an admin (0 user, 1 admin, 2 banned, 3 logged in)
                                    t = threading.Thread(target = handle_authenticated_user)
                                    t.start()
                                else:
                                    pass
                            else:
                                client.send("Incorrect message, try again")

                    
                        



        except:
            # If an error occurs, remove the client and their nickname, then close the connection
            index = clients.index(client)
            clients.remove(client)
            client.close()
            # nickname = nicknames[index]
            # broadcast(f"{nickname} has left the chat.".encode(), client)
            # nicknames.remove(nickname)
            # print(f"Active Connection : {threading.active_count()}")
            break


if __name__ == "__main__":
    client_listener()
