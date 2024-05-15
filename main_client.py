# main client program
import socket
# import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip_addr = socket.gethostbyname(socket.gethostname())
port = 3456

# connection_message
connection_message = (f"\nWhat do you want to do?"
                      f"\n1.Signup"
                      f"\n2.Login"
                      f"\n3.Admin Login"
                      f"\nEnter your choice (Number)--->")

# no user

# wrong admin login

# nick

# username, adusername

# password, adpassword

# function_options


client.connect((ip_addr, port))

while 1:

    message = client.recv(30).decode('utf-8')

    if message == "connection_message":
        print(connection_message)
        choice = input()
        client.send(choice.encode())







