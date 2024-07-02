import socket
import time
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = (socket.gethostbyname(socket.gethostname()))
port = 2000

client.connect((IP_ADDR, port))

while True:
    request = input("Enter a command: ")
    if request.split(" ")[0] == "RETR":  
        filename = request.split(" ")[1]
        client.send(request.encode("utf-8"))
        reply = client.recv(1024).decode("utf-8")
        if reply == "File not found":
            print("File not found")
            continue
        else:
            client.send("ACK filesize".encode("utf-8"))
            print("Size of file:", reply)
            received_bytes = 0

            with open(request.split(" ")[2], "wb") as file:
                while received_bytes < int(reply):
                    data = client.recv(1024)
                    received_bytes += len(data)
                    file.write(data) 
            print("File downloaded successfully")
            continue
    
    elif request.split(" ")[0] == "STOR":
        filename = request.split(" ")[1]
        # filesize = os.path.getsize(filename)
        client.send(request.encode("utf-8"))
        reply = client.recv(1024).decode("utf-8")
        print(reply)
        if reply == "File already exists, do you want to overwrite?":
            reply = input(reply + " (Y/N): ")
            client.send(reply.encode("utf-8"))
            if reply == "N":
                print(client.recv(1024).decode("utf-8"))
                continue
        elif reply == "Starting upload.":
            client.send("ACK".encode("utf-8"))
        elif reply == "Please Login first":
            continue
        print(client.recv(1024).decode("utf-8"))
        with open(filename, "r") as file:
            data = file.read().encode("utf-8")
            client.send(f"{len(data)}".encode("utf-8"))
            client.sendall(data)
            print(client.recv(1024).decode("utf-8"))

        print("File uploaded successfully")
        continue
    elif request.split(" ")[0] == "QUIT":
        client.send(request.encode("utf-8"))
        print(client.recv(1024).decode("utf-8"))
        break
    elif request.split(" ")[0] == "ADDUSER":
        client.send(request.encode("utf-8"))
        reply = client.recv(1024).decode("utf-8")
        if reply != "User already exists" or reply != "Please Login first":
            print(client.recv(1024).decode("utf-8"))
        continue
    elif request.split(" ")[0] == "DELUSER":
        client.send(request.encode("utf-8"))
        reply = client.recv(1024).decode("utf-8")
        if reply == "User directory not empty, do you want to delete anyway?":
            reply = input(reply + " (Y/N): ")
            client.send(reply.encode("utf-8"))
            reply = client.recv(1024).decode("utf-8")
            print(reply)

            continue
        else:
            print(reply)
        continue
    client.send(request.encode("utf-8"))
    reply = client.recv(1024).decode("utf-8")
    print(reply)