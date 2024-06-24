I have created two files name ftpserver and ftp client

From client we can perform tasks like storing the file on server, retriving the file from server, listing all the files already present in server

Storing the file to server, retriving it from server along with list function work completely fine

Whenever a client connects to the server it first ask username. If username is already present in the list that it asks for password and if it matches the useranme password key present in the fserver it lets the userin

Also if username is not already listed, he can create a new user.

Problem with this code is that it can not handle exceptions for ex. file  that you want to transfer to server , if its not present in your working directory it will give error andget stuck midway.

It will work if user give the right set of command. like to store a file in server the file, the client has to write the right filename or my code won't work

I am unable to do this exception handling

I have also tried making admin. For that i created a new python file named admin. But integrating it with server and client was problem as the code got stuck midway due to some improper aapplication of threading(i guess)

You can check the integrated code that does not work its named ftpserver copy and ftp client copy.py
