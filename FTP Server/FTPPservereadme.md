>#FTP Server

>-This is a simple FTP (File Transfer Protocol) server implemented in Python using sockets. The server allows users to authenticate, list files, retrieve files, store files, and execute admin commands for managing users.

>-## Features

>- User authentication with username and password
>- Commands for regular users:
 > - LIST: List files in the current directory
  >- RETR <filename>: Retrieve a file from the server
  >- STOR <filename>: Store a file on the server
  >- QUIT: Disconnect from the server
>- Admin commands (requires admin privileges):
  >- ADDUSER <username> <password>: Add a new user to the server
  >- DELUSER <username>: Delete a user from the server
  >- BAN <username>: Ban a user from the server
  >- UNBAN <username>: Unban a user from the server
  >- QUIT: Disconnect from the server
>##Usage

>- Connect to the FTP server using an FTP client application.
>- Use the `USER <username>` command to authenticate with your username.
>- Enter your password when prompted with the `PASS <password>` command.
>- Execute commands such as LIST, RETR, STOR for regular user functionalities.
>- For admin commands, login as the admin user and provide the admin password when prompted.
>- Execute admin commands like ADDUSER, DELUSER, BAN, UNBAN for managing users.

>##Configuration

>- Update the `users` dictionary in the code to include your desired user accounts and passwords.
>- Optionally, modify the `admins` dictionary to include admin usernames and passwords.


