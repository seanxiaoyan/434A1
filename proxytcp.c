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
#include <netdb.h>
     
#define  PORT_SERVER 31234
#define  PORT_PROXY 34321
#define  BACKLOG 10
#define  MAXDATASIZE 100
int main(int argc, char *argv[]){
    int  serverfd, proxyfd, clientfd, buf_len;
    struct  sockaddr_in server, proxy, client;

    struct hostent *host;
    socklen_t  addrlen;
    char  buf_server[MAXDATASIZE];
    char  buf_proxy[MAXDATASIZE];

    int opt =1;
    addrlen =sizeof(client);

    if((host=gethostbyname(argv[1]))==NULL){
        printf("gethostbyname()error\n");
        exit(1);
    }
    memset(&server, 0, sizeof(server));
    memset(&proxy, 0, sizeof(proxy));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT_SERVER);
    server.sin_addr =*((struct in_addr *)host->h_addr);
    proxy.sin_family=AF_INET;
    proxy.sin_port=htons(PORT_PROXY);
    proxy.sin_addr.s_addr= htonl (INADDR_ANY);

    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Creating  server socket failed.");
        exit(1);
    }
    if((proxyfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Creating  proxy socket failed.");
        exit(1);
    }
  
    if(setsockopt(proxyfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == -1){
        perror("setsockopt failed");
        exit(1);
    }
    if(bind(proxyfd, (struct sockaddr *)&proxy, sizeof(proxy)) == -1) {
        perror("Bind failed.");
        exit(1);
    }   
    if(listen(proxyfd,BACKLOG)== -1){ 
        perror("listen failed\n");
        exit(1);
    }

    while(1){
        memset(buf_server,0,MAXDATASIZE);
        memset(buf_proxy,0,MAXDATASIZE);
        if((clientfd = accept(proxyfd,(struct sockaddr*)&client,&addrlen))==-1) {
            perror("accept()error\n");
            exit(1);
        }
        printf("proxy Got a connection from client ip %s, prot %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));

        if((buf_len = recv(clientfd,buf_proxy,MAXDATASIZE,0)) == -1){
            printf("recv() error\n");
            exit(1);
        }
        printf("proxy receive from client: %s\n", buf_proxy);
        
        if(connect(serverfd,(struct sockaddr *)&server,sizeof(server))==-1){
            printf("connect()error\n");
            exit(1);
        }
        send(serverfd,buf_proxy,strlen(buf_proxy),0);
        if((buf_len = recv(serverfd,buf_server,MAXDATASIZE,0)) == -1){
            printf("recv() error\n");
            exit(1);
        }
        
        send(clientfd,buf_server,strlen(buf_server),0);
        
    }
    return 0;
}
