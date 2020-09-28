/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h> 
#include<arpa/inet.h> 
#include<fcntl.h> 
#include <strings.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen,file;
     char buffer[1024], filename[100];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     /* create socket */
     printf("Waiting For The Request From Client...\n");
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     /* fill in port number to listen on. IP address can be anything (INADDR_ANY) */

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     /* bind socket to this port number on this machine */

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     /* listen for incoming connection requests */

     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     /* accept a new request, create a newsockfd */
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     recv(newsockfd,filename,sizeof(filename),0);

    printf("Request For The File. %s\n", filename);
    file=open(filename,O_RDONLY);
    if(file<0)
        send(newsockfd,"file not found\n",20,0);
    else
        while((n=read(file,buffer,sizeof(buffer)))>0) 
  // read the input being sent by the client
                send(newsockfd,buffer,n,0);
    printf("Request Has Been Sent...\n");
    close(file);
    
     return 0; 
}
