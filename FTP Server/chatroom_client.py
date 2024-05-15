import socket
import threading

# Ask the user for a nickname
nick = input("Enter a nickname : ")

# Create a socket object for the client
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

# Connect to the server
client.connect((IP_ADDR,port))

# Receive a message from the server
message = client.recv(1024).decode()

# If the message from the server is asking for a nickname, send the nickname
if message == "NICK?":
    client.send(nick.encode())

# Function to send messages to the server
def send_message():
    while True:
        try:
            message = input()  # Take input from the user
            client.send(f"{nick} : {message}".encode())  # Send the message to the server along with the nickname
            
        except:
            print("An error occurred!")
            client.close()
            break

# Function to receive messages from the server
def receive_message():
    while Tru