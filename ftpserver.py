import socket
import threading
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

server.bind((IP_ADDR,port))

server.listen()
print(f"Server is listening on {IP_ADDR}:{port}")

users={}
clients=[]
file_names=[]

def new_client():
    while True:
        client, address = server.accept()
        # role=client.recv(1024).decode()
        # if(role=="ADMIN"):
        #     print(f"ADMIN is connected to the server")
            
            
        print(f"\nConnection received from {address}")
        username=client.recv(1024).decode()
        clients.append(client)
        if username in users.keys():
            passwd="Password?"
            client.send(passwd.encode())
            passwd = client.recv(1024).decode()
            
            if users[username]==passwd:
                print(f"Welcome aboard {username}")
            else:
                print(f"Incorrect Password")
                client.close()
                break
        else:
            message="New Account"
            client.send(message.encode())
            passwd = client.recv(1024).decode()
            passwd1= client.recv(1024).decode()
            if(passwd==passwd1) :
                users[username]=passwd
                print(f"New account created successfully with username : {username}")
            else:
                client.close()
                print(f"Password did not match")
                
        print(f"Active Connection : {threading.active_count()}")
        t = threading.Thread(target=handle_client, args=(client,))
        t.start()  
        
def handle_client(client):
    while True:
        try:
            message = client.recv(1024).decode()
            if message== "STORE FILE":
                try:
                        filename=client.recv(1024).decode()
                    # if filename in file_names:
                    #     print("File already present on server")
                    # else:
                        file_names.append(filename)
                        file= open(filename ,'w')
                        
                        data=client.recv(1024).decode()
                        print(f"{filename} added")
                        # while(data):
                            
                        #     if not data:
                        #         break
                        #     else:
                        file.write(data)
                        #         data=client.recv(1024).decode()
                        file.close()
                except:
                    print(" Fileis already present on server")
                    
                
            elif message== "Retriving FILE":
                filename=client.recv(1024).decode()
                if filename in file_names:
                    file = open(filename , 'r')
                    data=file.read()
                    print(data)
                    # while(data):
                    client.send(data.encode())
                    #     data=file.read()
                    file.close()
                else:
                    print("No Such file present")
                
                
            elif message=="list":
                length=len(file_names)
                while(length):
                    client.send(file_names[length-1].encode())
                    length-=1
                client.send("done".encode())
        except:
            client.close()  
            break           

               

        
if __name__ == "__main__":
    new_client()