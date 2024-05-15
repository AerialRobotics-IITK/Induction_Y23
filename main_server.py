# main server program
import socket
import threading

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip_addr = socket.gethostbyname(socket.gethostname())
port = 3456

server.bind((ip_addr, port))

server.listen(5)
print(f"\nServer has started listening on {ip_addr}:{port}")

user_data = []
number_of_active_clients = 0


def handle_signup(client):
    client.send("nick".encode())
    nick = client.recv(20).decode('utf-8')
    client.send("username".encode())
    username = client.recv(20).decode('utf-8')
    client.send("password".encode())
    password = client.recv(20).decode('utf-8')

    return nick, username, password


def handle_login(client):
    client.send("username".encode())
    try_username = client.recv(20).decode('utf-8')
    client.send("password".encode())
    try_password = client.recv(20).decode('utf-8')

    for data in user_data:
        if try_username == data[1] and try_password == data[2]:
            return data

    return '-1', '-1', '-1'


def handle_functions(client):
    client.send("function_options".encode())
    option = client.recv(10).decode('utf-8')
    # 1.List
    # 2.Retrieve
    # 3.Store
    # 4.Quit

    #if option=='1':

    #if option=='2':

   # if option=='3':

   # if option=='4':




def handle_admin_login():
    client.send("adusername".encode())
    try_username = client.recv(20).decode('utf-8')
    client.send("adpassword".encode())
    try_password = client.recv(20).decode('utf-8')

    if try_username == "dny" and try_password == "123":
        return 1

    else:
        return 0


def handle_admin_functions():
    # change this
    return 0


def handle_client(client, address):
    print(f"\nConnection established with {address}")
    while 1:
        client.send("connection_message".encode())
        answer = client.recv(10).decode('utf-8')
        if answer == "1":
            user_data.append(handle_signup(client))

        if answer == "2":
            result = handle_login(client)
            if result[0] != '-1':
                handle_functions(client)
            else:
                ########
                client.send('no user'.encode())
                ########


        if answer == "3":
            result = handle_admin_login()
            if result:
                handle_admin_functions()

            else:
                client.send("wrong admin login".encode())


print(f"\nWaiting for connection...")
while 1:
    client, address = server.accept()
    number_of_active_clients += 1
    print(f"\nNumber of active connections : {number_of_active_clients}")
    t = threading.Thread(target=handle_client, args=(client, address))
    t.start()
    s