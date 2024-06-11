# FTP server
 One can use `py .\Assignment2server.py` or `python .\Assignment2server.py` or `python3 .\Assignment2server.py` to run the server file.<br>
### This server uses the following commands for user as a client -
1) `USER <username> <password>` - to authenticate the user by its username and password.<br> 
2) `LIST` - to list the files in the directory.<br>
3) `RETR <filename>` - to retreive a file from the directory.<br>
4) `STOR <filename> <data>` - to store a file in the directory.<br>
5) `QUIT` - to quit the server.<br>

### This server uses the following commands for admin as a client -
1) `ADDUSER` - to add a user to the server database.
2) `DELUSER` - to delete a user from server database.
3) `BAN` - to ban the user from the server.
4) `UNBAN` - to unban a user from the server.