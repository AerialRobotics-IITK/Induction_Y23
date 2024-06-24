import socket
import threading

username=input("Enter a username: ")


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_ADDR = socket.gethostbyname(socket.gethostname())
port = 1234
client.connect((IP_ADDR,port))
client.send("USER".encode())
client.send(username.encode())
connecting_message= client.recv(1024).decode()

if connecting_message =="Password?":
    passwd=input("Enter the password: ")
    client.send(passwd.encode())
elif connecting_message=="New Account":
    print(f"New account is created with username {username}")
    passwd=input("Enter the password: ")
    client.send(passwd.encode())
    passwd1 =input("Enter above passwd again: ")
    client.send(passwd1.encode())

def file_transfer():
    message="STORE FILE"
    client.send(message.encode())
    filename = input("Please Enter the file name you want to add :")
    filename1= input("please enter the new filename for the server: ")
    client.send(filename1.encode())
    try:
        file= open(filename, 'r')
        data =file.read()
        # while data: 
        client.send(data.encode()) 
        #     data = file.read() 
        file.close() 
    except: print("You have entered a wrong file address")
    
def file_retriving():
    try:
        message="Retriving FILE"
        client.send(message.encode())
        filename =input("Please input the file name you want to retrieve")
        client.send(filename.encode())
        data=client.recv(1024).decode()
        filename = input("Please input the name with which you want to store it in your device: ")
        file = open(filename, 'w')
        # while(data):           
        file.write(str(data))
    except:
        print("Given file is not present on server")
def list1():
    message= "list"
    client.send(message.encode())
    list23=[]
    data=client.recv(1024).decode()
    
    while(data!="done"):
        list23.append(data)
        data=client.recv(1024).decode()
    print(list23)
    
if __name__ == "__main__":
    print("Welcome to the Server. Please follow below commands:")
    print("To store the file on server give command : STOR")
    print("To retrieve a file from the server give command : RETR")
    print("To list the file present on server: LIST")
    print("To quit the server: QUIT")
     
    while True:   
            command = input("Enter the command: ") 
            if command == "STOR":
                file_transfer()
            elif command == "RETR":
                file_retriving()
            elif command=="LIST":
                list1()
            elif command == "QUIT":
                print("Adios amigo!!!!!")
                break
            else: print("The given command is wrong")
        
    
        

    
    
    
