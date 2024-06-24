import socket
import threading
admin = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

admin.connect((IP_ADDR,port))

print(f"Server is listening on {IP_ADDR}:{port}")

admin.send("ADMIN".encode())

if __name__ == "__main__":
    print("Welcome to the Server. Please follow below commands:")
    print("To ADD a user: ADD")
    print("To DELETE a user : DEL")
    print("To BAN a user: BAN")
    print("To UNBAN a user: UNBAN")
    while True:
            command = input("Enter the command: ") 
            if command == "ADD":
                admin.send("ADD".encode())
                username= input("Enter username you want to add: ")
                admin.send(username.encode())
                passwd=input("Enter the passwd for the username: ")
                admin.send(passwd.encode())
                
            elif command == "DEL":
                admin.send("DEL".encode())
                username= input("Enter username you want to add: ")
                admin.send(username.encode())
                
            elif command=="BAN":
                admin.send("BAN".encode())
                username= input("Enter username you want to add: ")
                admin.send(username.encode())
                
            elif command == "UNBAN":
                admin.send("UNBAN".encode())
                username= input("Enter username you want to add: ")
                admin.send(username.encode())
                
            else: 
                print("The given command is wrong")
                break
    
