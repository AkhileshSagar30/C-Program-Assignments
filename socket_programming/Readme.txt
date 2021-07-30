# socket-programming
Question: Update the code for the server and client program which is shared earlier, such that it can perform the following.

a) The sever should look for the file requested by the client in the current working directory. If the file is available, then it should read the file and send the contents of the files to the client. The client should receive the file contents and display it.

b) After displaying all the contents of the file, the client should close.

c) Server program should receive the port number as command-line argument.
Syntax: ./server_name port_num
Eg: ./server 2999

d) Client program should receive the server’s IP address, port number and the filename as command-line argument.
Syntax: ./client_name ip_address_of_server port_num file_name
Eg: ./client localhost 2999 hello.c
