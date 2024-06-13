import socket
import time
import os


def getlist(client):
    client.send('1'.encode())
    received_data = client.recv(1024).decode() 
    print("\nList of files in the server:\n")
    for l in received_data:
        if l=='+':
            print()
            continue
        print(l,end='')
    return

def retr(client, file_name):
    client.send('2'.encode())
    print("PROGRESS: code2 sent/",end='')
    time.sleep(1)
    client.send(str(file_name).encode())
    print("fn sent/",end='')
    newfilename = "(DFS)_" + str(file_name)
    print("new_fn created/",end='')
    msg=client.recv(1024).decode()
    if msg=="1":
        try:
            with open(newfilename, 'wb') as file:
                print("file op/",end='')
                file_bytes = b''
                print("entering receivingloop/",end='')
                while True:
                    print('.',end='')
                    if file_bytes.endswith(b"<KHTM>"): 
                        break
                    data = client.recv(1024)
                    file_bytes += data
                file_bytes=file_bytes[:-6]
                file.write(file_bytes)
                print("\nFile downloaded successfully!\n")
        except socket.error:
            print("Error receiving file:", file_name)
    elif msg=="0":
        print("\n\nFile not present in server!\n")
        return

def stor(client, file_name):
    client.send('3'.encode())
    if not os.path.exists(file_name):
        print(f"File '{file_name}' does not exist on client machine.")
        client.send("File not found".encode())
        return

    newfilename = "(UTS)_" + file_name
    client.send(str(newfilename).encode('cp1252'))
    try:
        with open(file_name, 'rb') as file:
            data = file.read()
            client.sendall(data)
            client.send(b"<KHTM>")
        print(f"\nFile '{file_name}' uploaded successfully!")
    except socket.error:
        print(f"Error uploading file: {file_name}")

def main():
    ip = input("IP: ")
    port = 6968
    uname = input("\nEnter your username: ")
    passwd = input("Enter your password: ")

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    client.connect((ip,port))
    if client.recv(1024).decode()=="uname?":
        client.send(uname.encode())
    if client.recv(1024).decode()=="passwd?":
        client.send(passwd.encode())
    if client.recv(1024).decode()=="connected":
        print("\n\nConnection Successful\n\n")
        while True:
            try:
                ch = input("\n\nPress 1: List Files in the server\nPress 2: Retrieve files from the server\nPress 3: Store files in the server\nPress 4: Quit\n")
                if ch not in ['1', '2', '3', '4']:
                    print("Invalid choice. Please enter a number between 1 and 4.")
                    continue
                if ch == '1':  # Listdir
                    getlist(client)
                elif ch == '2':
                    file_name = input("Enter the name of the file to be retrieved from the server: ")
                    retr(client, file_name)
                elif ch == '3':
                    file_name = input("Enter the name of the file to be stored in the server:")
                    stor(client, file_name)
                elif ch == '4':
                    client.send('4'.encode())
                    client.close()
                    print("Disconnected from server.")
                    break
            except KeyboardInterrupt:
                print("\nExiting...")
                client.send('4'.encode())
                client.close()
                break
    elif client.recv(1024).decode()=="BAN":
        print("You are Banned from the server Contact Admin ")
    else:
        print("Authentication failed. \n Contact Admin\n\n")

if __name__ == "__main__":
    main()