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
#define  MAXDATASIZE 4000
#define  SIZE 100
int main(int argc, char *argv[]){
    int  serverfd, proxyfd, buf_len;
    struct  sockaddr_in server, proxy, client;

    struct hostent *host;
    socklen_t  addrlen_proxy, addrlen_server;
    char  buf_server[SIZE];
    char  buf_proxy[SIZE];
    char weather_all[MAXDATASIZE];


    addrlen_proxy =sizeof(proxy);
    addrlen_server =sizeof(server);


    if((host=gethostbyname(argv[1]))==NULL){
        printf("gethostbyname()error\n");
        exit(1);
    }
    
    memset(&proxy, 0, sizeof(proxy));
    proxy.sin_family=AF_INET;
    proxy.sin_port=htons(PORT_PROXY);
    proxy.sin_addr.s_addr= htonl (INADDR_ANY);
    if((proxyfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("Creating  proxy socket failed.");
        exit(1);
    }
  
    if(bind(proxyfd, (struct sockaddr *)&proxy, sizeof(proxy)) == -1) {
        perror("Bind failed.");
        exit(1);
    }   



    while(1){
        memset(buf_server,0,SIZE);
        memset(buf_proxy,0,SIZE);
        memset(&server, 0, sizeof(server));
        server.sin_family=AF_INET;
        server.sin_port=htons(PORT_SERVER);
        server.sin_addr =*((struct in_addr *)host->h_addr);
        if((buf_len = recvfrom(proxyfd,buf_proxy,SIZE,0,(struct sockaddr*)&proxy, &addrlen_proxy)) == -1){
            printf("recv() error\n");
            exit(1);
        }
        printf("proxy receive from client: %s\n", buf_proxy);




        if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
            perror("Creating  server socket failed.");
            exit(1);
        }

        if (strcmp(buf_proxy,"all")==0){
            
            sendto(serverfd,"Monday",6,0, (struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0, (struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Weather information for the week:\nMonday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);

            if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
                perror("Creating  server socket failed.");
                exit(1);
            }

            sendto(serverfd,"Tuesday",7,0,(struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0, (struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Tuesday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);


            if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
                perror("Creating  server socket failed.");
                exit(1);
            }

            sendto(serverfd,"Wednesday",9,0, (struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0,(struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Wednesday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);

            if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
                perror("Creating  server socket failed.");
                exit(1);
            }

            sendto(serverfd,"Thursday",8,0, (struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0, (struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Thursday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);

            if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
                perror("Creating  server socket failed.");
                exit(1);
            }

            sendto(serverfd,"Friday",6,0, (struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0, (struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Friday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);

            if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
                perror("Creating  server socket failed.");
                exit(1);
            }

            sendto(serverfd,"Saturday",8,0, (struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0, (struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Saturday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);

            if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
                perror("Creating  server socket failed.");
                exit(1);
            }

            sendto(serverfd,"Sunday",6,0, (struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,SIZE,0, (struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            strcat(weather_all,"Sunday: ");
            strcat(weather_all,buf_server);
            close(serverfd);
            memset(buf_server,0,SIZE);
            sendto(proxyfd,weather_all,strlen(weather_all),0, (struct sockaddr*)&proxy, addrlen_proxy);
            memset(weather_all,0,MAXDATASIZE);
        }
        else{
            sendto(serverfd,buf_proxy,strlen(buf_proxy),0,(struct sockaddr*)&server, addrlen_server);
            if((buf_len = recvfrom(serverfd,buf_server,MAXDATASIZE,0,(struct sockaddr*)&server, &addrlen_server)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            sendto(proxyfd,buf_server,strlen(buf_server),0, (struct sockaddr*)&proxy, addrlen_proxy);
        }
        
        close(serverfd);
        
        
    }
    close(proxyfd);
    return 0;
}
