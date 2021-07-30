#include <stdio.h>
#include <netinet/in.h>
#include <string.h> 
#include<arpa/inet.h> 
#include<fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}
//send(), recv() methods for sending and recieving.
int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    // -----------------
    char filename[100];
    strcpy(filename,argv[3]);
    /* create socket, get sockfd handle */

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* fill in server address in sockaddr_in datastructure */

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    /* connect to server */

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    // ------------------
    printf("Sending The Request...\n");
    send(sockfd,filename,sizeof(filename),0);
    /* ask user for input */

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);

    /* read reply from server */

    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    return 0;
}
