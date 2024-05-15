# File Sharing Server

This is a simple file sharing server implemented in Python using sockets. The server allows users to create accounts, upload files, download files, and perform administrative tasks such as adding, deleting users, and banning/unbanning users.

## Prerequisites
```bash
pip install -r requirements.txt #To use the same version of pandas that I used.
```
## Usage

1. Run the server script:

    ```bash
    python ./Server/Server.py #Considering you are in the FTP Server directory.
    ```

2. Connect to the server using the client application.
    ```bash
    python ./Client/client.py #Considering you are in the FTP Server directory.
    ```
## Commands

- `USER <username>`: Log in with the specified username.
- `PASS <password>`: Enter the password for authentication.
- `LIST`: List files in the user's directory.
- `RETR <filename> <filename>`: Download a file from the server.First filename is the name of the file on the server and the second is the name by which you want to save on your local machine.
- `STOR <filename> <filename>`: Upload a file to the server.First filename is the name of the file on your local machine second is the name of the file by which you want to save on the server.
- `QUIT`: Terminate the session.

## Admin Commands

- `ADDUSER <username> <password>`: Add a new user to the system (admin only).
- `DELUSER <username>`: Delete a user from the system (admin only).
- `BAN <username>`: Ban a user from accessing the server (admin only).
- `UNBAN <username>`: Unban a user (admin only).

## Admin credentials
- `Username` : ADMIN
- `Password` : ADMIN

## Some exciting features
1. The SERVER_LOG.txt is the file that contains all information about when the server started, when and from where the client got connected , what commands were received from the client.
2. The Passwords are hashed in User_Pass.csv , therefore the clients can be carefree about their passwords getting leaked.