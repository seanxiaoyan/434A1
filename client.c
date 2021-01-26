/*
Name: Xiaoyan Xu
Student  Number: 11229743
NSID: xix799
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define  MAXDATASIZE 100
#define INPUTSIZE 20

void getInput(char *buffer){
    char input[INPUTSIZE];
    printf("Enter the day: ");
    fgets(input, sizeof(input), stdin);
    strcpy(buffer,input);
    buffer[strcspn(buffer,"\n")]='\0';

}

int validateInput(char *buffer){
    int flag = -1;
    if ((strcmp(buffer,"Monday") == 0)||
    (strcmp(buffer,"Wednesday") == 0)||
    (strcmp(buffer,"Thursday") == 0)||
    (strcmp(buffer,"Friday") == 0)||
    (strcmp(buffer,"Tuesday") == 0)||
    (strcmp(buffer,"Saturday") == 0)||
    (strcmp(buffer,"Sunday") == 0))
    {
        flag = 1;
    }
    else if (strcmp(buffer,"quit") == 0){
        flag = 0;
    }
    return flag;
}
 
int main(int argc, char *argv[]){
    int  socketfd, num, len, PORT, flag;
    char  buf[MAXDATASIZE];
    char buffer[INPUTSIZE];
    struct hostent *host;
    struct sockaddr_in server;
    char msg[INPUTSIZE];
    flag = 0;
    while(1){
        getInput(buffer);
        switch (validateInput(buffer)){
            case -1:
            printf("invalid day\n");
            break;
            default:
            strcpy(msg,buffer);

            if((host=gethostbyname(argv[1]))==NULL){
                printf("gethostbyname()error\n");
                exit(1);
            }

            if((PORT=atoi(argv[2]))==0){
                printf("get port error\n");
                exit(1);
            }


            memset(&server, 0, sizeof(server));
            server.sin_family= AF_INET;
            server.sin_port = htons(PORT);
            server.sin_addr =*((struct in_addr *)host->h_addr);
            if((socketfd=socket(AF_INET, SOCK_STREAM, 0))==-1){
                printf("socket()error\n");
                exit(1);
            }
            if(connect(socketfd,(struct sockaddr *)&server,sizeof(server))==-1){
            printf("connect()error\n");
            exit(1);
            }
            len = strlen(msg);
            send(socketfd, msg, len, 0);
           
            if (strcmp(msg,"quit")==0){
                flag=1;
                close(socketfd);
                
            }
            else{
                if((num=recv(socketfd,buf,MAXDATASIZE,0)) == -1){
                    printf("recv() error\n");
                    exit(1);
                }
                buf[num]='\0';
                printf("Message from server: %s\n",buf);
                close(socketfd);
            }
            
        }
        if(flag==1){break;}
    }
    return 0;
}
