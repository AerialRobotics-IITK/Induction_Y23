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
ban=[]

def new_client():
    while True:
        client, address = server.accept()
        print("yes")
        role=client.recv(1024).decode()
        print("yes")
        
        if(role=="ADMIN"):
            print(f"\nConnection received from {address}")            
            print(f"ADMIN is connected to the server")
            print(f"Active Connection : {threading.active_count()}")
            t = threading.Thread(target=admin_handle, args=(client,))
            t.start()  
        
            
        else:   
            print("yes") 
            print(f"\nConnection received from {address}")
            username=client.recv(1024).decode()
            clients.append(client)
            print("yes") 
            
            if (username in users.keys() and username not in ban):
                passwd="Password?"
                client.send(passwd.encode())
                passwd = client.recv(1024).decode()
                
                if users[username]==passwd:
                    print(f"Welcome aboard {username}")
                else:
                    print(f"Incorrect Password")
                    client.close()
                    break
            elif username in ban:
                print(f"{username} is banned from the server")
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
def admin_handle(admin):
    while True:
            message = admin.recv(1024).decode()
            if message == "DEL":
                username=admin.recv(1024).decode()
                del users[username]
                print(f"{username} has been deleted from the server by admin")
                
            elif message == "ADD":
                username=admin.recv(1024).decode()
                passwd=admin.recv(1024).decode()
                if username not in ban:
                    users[username]=passwd
                    print(f"{username} has been added to the server")
                
                
            elif message == "BAN":
                username=admin.recv(1024).decode()
                ban.append(username)
                print(f"{username} has been banned from the server")
                
                
            elif message =="UNBAN":
                username=admin.recv(1024).decode()
                ban.remove(username)
                print(f"{username} has been unbanned from the server")
                

                
                
        
        
                     

               

        
if __name__ == "__main__":
    new_client()