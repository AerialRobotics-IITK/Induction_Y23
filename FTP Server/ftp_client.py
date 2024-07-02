import socket
import os
import threading

# Ask the user for a nickname
nick = input("Enter a nickname : ")

# Create a socket object for the client
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234

# Connect to the server
client.connect((IP_ADDR,port))

def download_file(client):
    # bytes_size_bytes = client.recv(4)
    # bytes_size = int.from_bytes(bytes_size_bytes, byteorder='big')
    file_size_bytes = client.recv(8) # 8 chosen so that 1tb can fit
    file_size = int.from_bytes(file_size_bytes)
    print("File size:", file_size)
    filename_size_bytes = client.recv(8)
    filename_size = int.from_bytes(filename_size_bytes)
    print("Filename size:", filename_size)
    filename = client.recv(filename_size).decode()
    print("Filename:", filename)
    with open(filename, "wb") as f:
        file_data = 0
        while file_data < file_size:
            chunk = client.recv(file_size - file_data)
            if not chunk:
                break
            f.write(chunk)
            print("WRote a chunk")
            f.flush()
            file_data += len(chunk)
        f.close()
        #f.write(file_data)
    print("Written to file")

def upload_file(filepath: str,client: socket):
    try:
        file = open(filepath, "rb")
    except:
        print("failed to open file")
        return False
    path, filename = os.path.split(filepath)
    filename+="g"
    data = file.read()
    client.send(len(filename).to_bytes(8))
    client.send(filename.encode())
    client.send(len(data).to_bytes(8))
    client.sendall(data)


def handle_connection(client):
    while True:
        logged_in = False
        mg = client.recv(1024)
        print(mg)
        message = input()
        client.send(message)
        response_int = int.from_bytes(client.recv())
        match response_int:
            case 20: # just read
                mg = client.recv(1024)
                print(mg)
            case 




        



# Receive a message from the server
message = client.recv(1024).decode()

# If the message from the server is asking for a nickname, send the nickname
if message == "USERNAME?":
    client.send(nick.encode())

message = client.recv(1024).decode()
if message[0] == "W":
    print("hello", message)
    filebytes = b''
    with open("test.md", "rb") as f:
        filebytes += f.read()
    upload_file("test.md", client)
    # download_file(client)




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
    while True:
        try:
            messages = client.recv(1024)  # Receive messages from the server
            print(messages.decode())  # Print the received messages
        except:
            print("An error occurred!")
            client.close()
            break

# Create two threads, one for sending messages and one for receiving messages
receive_thread = threading.Thread(target=send_message)
send_thread = threading.Thread(target=receive_message)

# Start the threads
receive_thread.start()
send_thread.start()
