import socket
import threading
import os 

clients = []
nicknames = []
banned =[]
users = ['u0','u1', 'u2','u3','u4','u5', 'ADMIN']
passds = ['u0pass','u1pass', 'u2pass','u3pass','u4pass','u5pass', 'ADMINpass']

def broadcast(message, sender_client):
    for client in clients:
        if client != sender_client:
            client.send(message.encode('utf-8'))
            
def get(client, filename):
    try:
        with open(filename, 'r') as infile:
            for line in infile:
                client.sendall(line.encode())    
        end_message = "EOF-STOP"
        client.sendall(end_message.encode())
    except Exception as e:
        print(e)
        error_message = ("There has been an error sending the requested file. " + filename + " might not exist")
        client.sendall(error_message.encode())
    return ""

def put(client, data):
    filename = data.split(' ')[1]
    print("Recieved File: "+filename)
    try:
        data = client.recv(1024).decode()
        with open(filename, 'w') as outfile:
            while(data):
                outfile.write(data)
                data = client.recv(1024).decode()
                if "EOF-STOP" in data:
                    stop_point = data.find("EOF-STOP")
                    outfile.write(data[:stop_point])
                    return data[stop_point+8:]
    except Exception as e:
        print(e)
        error_message = "There has been an error recieving the requested file."
        client.sendall(error_message.encode())
        return ""

def listt(client):
    dir = os.listdir("./")
    client.send("\n".join(dir).encode())
    return ""

def admin(client):
    message = client.recv(1024).decode()
    command = message.split(' ')[0].upper()
    if command == "ADDUSER":
        users.append(message.split(' ')[1])
        passds.append(message.split(' ')[2])
        print("User Added Sucessfully")
    elif command == "DELUSER":
        users.remove(message.split(' ')[1])
        passds.remove(message.split(' ')[2])
    elif command == "BAN":
        banned.append(message.split(' ')[1])
    elif command == "UNBAN":
        banned.remove(message.split(' ')[1])
    else : print("No such command found")

    return

def user(username):
    if username in banned:
        print("This user is banned")
        return
    for user in users :
        if user == username :
            print("User found. Please enter your password in this format PASS <password>")
            return 1
    return 0

def passd(pa, us, client):
    for user,val in users:
        if user == us:
            if passds[val]== pa:
                if us == "ADMIN": 
                    print("You have logged in as Admin")
                    admin(client)
                    return ""
                print("Login Success")
    return ""

def handle_client(client):
    while True:
        try:
            command , remainder = "", "l"
            if remainder == "":
                message = client.recv(1024).decode()
                command = message.split(' ')[0].upper()
                broadcast(message, client)
            else:
                data = remainder
                space = remainder.find(' ')
                command = remainder[:space].upper()
                remainder = ""
            if command in command_list:
                if command == "QUIT":
                    print("Client quitting")
                    client.sendall(command.encode("utf-8"))
                    client.close()
                elif command == "RETR":
                    filename = data.split(' ')[1]
                    get(client, filename)
                elif command == "STOR":
                    remainder = put(client, data)
                elif command == "LIST":
                    remainder = listt(client)
                elif command == "USER":
                    username = data.split(' ')[1]
                    if(user(username)):
                        message = client.recv(1024).decode()
                        command = data.split(' ')[0]
                        if command == "PASS":
                            password = data.split(' ')[1]
                            remainder = passd(password, username, client)
                    else : print("No such user found")
                else :
                    print(data)
                    client.sendall(data.encode())
        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()
            nickname = nicknames[index]
            broadcast(f"{nickname} has left the chat.".encode(), client)
            nicknames.remove(nickname)
            print(f"Active Connection : {threading.active_count()}")
            break

def accept_client():
    while True:
        client, address = server.accept()
        print(f"\nConnection received from {address}")
        client.send("NICK?".encode())
        nick = client.recv(1024).decode()
        clients.append(client)
        nicknames.append(nick)
        print(f"\nNickname of the client is {nick}")
        print(f"Active Connection : {threading.active_count()}")
        client.send("\nYou are connected to the server".encode())
        broadcast(f"\n{nick} has joined the chat.", client)
        t = threading.Thread(target=handle_client, args=(client,))
        t.start()

command_list = ["QUIT","RETR","STOR","LIST","USER","PASS"]

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234
server.bind((IP_ADDR,port))

while True:
    server.listen()
    print(f"Server is listening on {IP_ADDR}:{port}")
    accept_client()

server.close()
