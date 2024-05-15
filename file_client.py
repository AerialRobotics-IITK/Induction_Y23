import os
import socket
import threading

IP_ADDR=socket.gethostbyname(socket.gethostname())
port=9999

def options():
    message=client.recv(1024).decode()
    print(message)
    op=input("Enter option number: ")
    client.send(op.encode())
    if op==1:
        message=client.recv(1024).decode()
        print(message)
    elif op==2:
        message=client.recv(1024).decode()
        filename=input(message)
        client.send(filename.encode())
        message=client.recv(1024).decode()
        if message=="\nFile not found":
            print(message)
        else:
            file=open(filename,"wb")
            while message!=b"<END>":
                message=client.recv(1024)
                file.write(message)
            file.close()
            print("\nFile received")
    elif op==3:
        file=open(filename,"rb")
        data=file.read(1024)
        while data:
            client.send(data)
            data=file.read(1024)
        client.send(b"<END>")
    elif op==4:
        client.close()


def connect():
    flag=1
    while flag:
        message=client.recv(1024).decode()
        if message=="Enter your Username: ":
            username=input(message)
            client.send(username.encode())
        message=client.recv(1024).decode()
        if message=="Enter your Password to login: ":
            password=input(message)
            client.send(password.encode())
            message=client.recv(1024).decode()
            if message=="Successfully connected to the server":
                while True:
                    message=client.recv(1024).decode()
                    print(message)
                    op=input("Enter option number: ")
                    client.send(op.encode())
                    if op==1:
                        message=client.recv(1024).decode()
                        print(message)
                    elif op==2:
                        message=client.recv(1024).decode()
                        filename=input(message)
                        client.send(filename.encode())
                        message=client.recv(1024).decode()
                        if message=="\nFile not found":
                            print(message)
                        else:
                            file=open(filename,"wb")
                            while message!=b"<END>":
                                message=client.recv(1024)
                                file.write(message)
                            file.close()
                            print("\nFile received")
                    elif op==3:
                        file=open(filename,"rb")
                        data=file.read(1024)
                        while data:
                            client.send(data)
                            data=file.read(1024)
                        client.send(b"<END>")
                    elif op==4:
                        client.close()
                        flag=0
                        break
                    else:
                        print("Password incorrect")
                        client.close()
                        flag=0
                        break
        elif message=="Enter a password to register: ":
            password=input(message)
            client.send(password.encode())
            message=client.recv(1024).decode()
            print(message)
            continue
        elif message=="You have been banned from this server":
            print(message)
            client.close()
            flag=0
        else:
            print("Connection unsuccessful")
            client.close()
            flag=0

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((IP_ADDR,port))

thread=threading.Thread(target=connect)
thread.start()




