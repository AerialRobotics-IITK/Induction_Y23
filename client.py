import socket
import threading
import struct
# Create a socket object for the client
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 5050
BUFFER_SIZE = 1024 # Standard chioce
# # Connect to the server
# client.connect((IP_ADDR,port))

def conn():
    # Connect to the server
    print ("Sending server request...")
    try:
        client.connect((IP_ADDR,port))
        print ("Connection sucessful")
    except:
        print( "Connection unsucessful. Make sure the server is online.")

def list_files():
    # List the files avaliable on the file server
    # Called list_files(), not list() (as in the format of the others) to avoid the standard python function list()
    print ("Requesting files...\n")
    try:
        # Send list request
        client.send("LIST")
    except:
        print ("Couldn't make server request. Make sure a connection has bene established.")
        return
    try:
        # First get the number of files in the directory
        number_of_files = struct.unpack("i", client.recv(4))[0]
        # Then enter into a loop to recieve details of each, one by one
        for i in range(int(number_of_files)):
            # Get the file name size first to slightly lessen amount transferred over socket
            file_name_size = struct.unpack("i", client.recv(4))[0]
            file_name = client.recv(file_name_size)
            # Also get the file size for each item in the server
            file_size = struct.unpack("i", client.recv(4))[0]
            print ("\t{} - {}b".format(file_name, file_size))
            # Make sure that the client and server are syncronised
            client.send("1")
        # Get total size of directory
        total_directory_size = struct.unpack("i", client.recv(4))[0]
        print ("Total directory size: {}b".format(total_directory_size))
    except:
        print ("Couldn't retrieve listing")
        return
    try:
        # Final check
        client.send("1")
        return
    except:
        print ("Couldn't get final server confirmation")
        return
    

    
def quit():
    client.send("QUIT")
    # Wait for server go-ahead
    client.recv(BUFFER_SIZE)
    client.close()
    print ("Server connection ended")
    return

print ("\n\nWelcome to the FTP client"  )
print("Pls enter Conn to connect with the server , ")
while True:
    # Listen for a command
    prompt = input("\nEnter a command: ")
    if prompt[:4].upper() == "CONN":
        conn()
        break
    

while True:
    signal = client.recv(1024).decode()

    while True:
        if signal == "Enter a username":
            username = input()

            client.send(username.encode())
            qwe = client.recv(1024).decode()
            if qwe == "You are a new user. Please enter a password ":
                password = input("Enter your password")
                client.send(password.encode())
            elif qwe == "You are an existing user, pls enter password":
                password = input("Enter you password")
                client.send(password.encode())
                message_3 = client.recv(1024).decode()
                if message_3 == "Logged in.. Congratulations":
                    print("Press L if u want to list , R to retrive, S to store and Q to Quit:")
                    prompt = input()
                    if prompt=='L':
                        list_files()
                    
                    if prompt=='Q':
                        quit()
                    
                      
                else: 
                    print("Your connection has been closed from the server side")
        else :
            break






    

    
    



