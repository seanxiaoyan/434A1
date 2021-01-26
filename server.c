/*
Name: Xiaoyan Xu
Student  Number: 11229743
NSID: xix799
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
     
#define  PORT 31234
#define  BACKLOG 10
#define  MAXDATASIZE 100

int main(){
    int  socketfd, connectfd, buf_len;
    struct  sockaddr_in server;
    struct  sockaddr_in client;
    socklen_t  addrlen;
    char  buf[MAXDATASIZE];

    int opt =1;
    addrlen =sizeof(client);

    memset(&server, 0, sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr= htonl (INADDR_ANY);

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Creating  socket failed.");
        exit(1);
    }
  
    if(setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == -1){
        perror("setsockopt failed");
        exit(1);
    }
    if(bind(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Bind failed.");
        exit(1);
    }   
    if(listen(socketfd,BACKLOG)== -1){ 
        perror("listen failed\n");
        exit(1);
    }
    if((connectfd = accept(socketfd,(struct sockaddr*)&client,&addrlen))==-1) {
        perror("accept()error\n");
        exit(1);
    }
    printf("You got a connection from cient's ip %s, prot is %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));
    send(connectfd,"Welcometo my server.\n",22,0);

    if((buf_len = recv(connectfd,buf,MAXDATASIZE,0)) == -1){
    printf("recv() error\n");
    exit(1);
    }
    buf[buf_len]='\0';

    printf("Client Message: %s\n",buf);
    close(connectfd);
    close(socketfd);
    return 0;
}
