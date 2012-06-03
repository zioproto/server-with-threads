#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>

static int connection(char *ipserver,int port);
static int sendmydata(int mysd, char* data);


//Crea un socket TCP con l'indirizzo IP e la porta che vengono passate, poi restituisce il socket descriptor
static int connection(char *ipserver,int port) {
    
        struct sockaddr_in      server_addr;
        int sockfd;
        struct hostent *resolvedIP;    //Struct needed for DNS name resolution
    
        //Create socket        

        if (((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )) {
                printf("Socket creation error\n");
                return(-1);
        }   
    
        memset((void *) &server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);    

        /*DNS Lookup*/
        resolvedIP = gethostbyname(ipserver);
        if (resolvedIP != NULL) {
        server_addr.sin_addr.s_addr = * (u_long *)resolvedIP->h_addr_list[0];
        }   
        else {
        server_addr.sin_addr.s_addr = inet_addr(ipserver);
        }   
    
        printf("connecting to server ...\nIP: %s\nPort: %d\n\n",inet_ntoa(server_addr.sin_addr),port);

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){ 
    
                printf("Error in remote socket connection\n");
                return(-1);    
        }   
        return(sockfd);
}


static int sendmydata(int mysd, char* data) {
    
        int sent;
    
        printf("Sending message on socket descriptor: %d\nMessage length will be %lu\n",mysd,strlen(data));
    
        if ( (sent = send(mysd,data,strlen(data),0)) < 0) {
                printf("Send error\n");
                return(sent);
        }   
    
        printf("I sent over the socket %d bytes\n",sent);
    
        return(sent);
    
}

int main(int argc , char **argv){

char hostname[20];
int port = 0;
char stringtosend[1000];

int socketdescriptor = 0;

if (argc < 4) {
    
        printf("Usage: ./tcpclient hostname port stringtosend \n");
        exit (1);
}

memset(hostname,0,sizeof(hostname));
memset(stringtosend,0,sizeof(stringtosend));


memcpy(hostname,argv[1],strlen(argv[1]));
port = atoi(argv[2]);
memcpy(stringtosend,argv[3],strlen(argv[3]));

 //Opens a TCP socket towards the selected IP address and port:
 socketdescriptor = connection(hostname,port);

 sendmydata(socketdescriptor, stringtosend);

return 0;

}
