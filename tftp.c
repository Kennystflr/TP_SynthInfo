//
// Created by knn64 on 12/11/24.
//
#include "utils.h"
#define WrongCommandget "Please enter a command in the following format : gettftp <host> <file>\r\n"
#define WrongCommandput "Please enter a command in the following format : puttftp <host> <file>\r\n"
#define BufferSize 512


void cmd_gettftp(int argc, char *argv[])
{
    char send_buffer[BufferSize] = "I Love TFTP\r\n";
    if (argc != 2)
    {
        write(STDIN_FILENO, WrongCommandget, strlen(WrongCommandget) );
    }
    else
    {
        struct addrinfo hints;
        memset(&hints,0,sizeof(struct addrinfo));
        hints.ai_protocol = IPPROTO_UDP;
        hints.ai_family = AF_INET;
        struct addrinfo * res;
        getaddrinfo(argv[1],"1069",&hints,&res);
        int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        sendRRQ(&sd,res,argv[2]);
        sendData(&sd,res,send_buffer,BufferSize);
        char host_name[128] = {0};
        char serv_name[128] = {0};
        getnameinfo(res->ai_addr,res->ai_addrlen,host_name,128,serv_name,128, NI_NUMERICHOST|NI_NUMERICSERV);


        write(STDOUT_FILENO,serv_name,128);
        write(STDOUT_FILENO, "OK\n", 2 );


    }
}




void sendRRQ(int *sd,struct addrinfo *res,char * file)
{
    char RRQBuf[BufferSize] ={0};
    RRQBuf[1]=1;//setting the OP Code
    sprintf(RRQBuf+2,"%s",file);
    RRQBuf[strlen(file)+3]=0;
    sprintf(RRQBuf+strlen(file)+3,"%s","netascii");
    sendto(*sd,&RRQBuf,strlen(file)+12,0,res->ai_addr,res->ai_addrlen);//RRQ sending

}

void sendWRQ(int *sd,struct addrinfo *res,char * file)
{
    char WRQBuf[BufferSize] ={0};
    WRQBuf[1]=2;//setting the OP Code
    sprintf(WRQBuf+2,"%s",file);
    WRQBuf[strlen(file)+3]=0;
    sprintf(WRQBuf+strlen(file)+3,"%s","netascii");
    sendto(*sd,&WRQBuf,strlen(file)+12,0,res->ai_addr,res->ai_addrlen);//WRQ sending

}

int recvACK(int *sd, struct addrinfo *res)
{
    char RecvBuf[BufferSize] ={0};
    recvfrom(*sd,&RecvBuf,BufferSize,0,res->ai_addr,res->ai_addrlen);


}

void cmd_puttftp(int argc, char *argv[])
{
    char send_buffer[BufferSize]={0};
    if (argc != 2)
    {
        write(STDIN_FILENO, WrongCommandput, strlen(WrongCommandput) );
    }
    else
    {
        struct addrinfo hints;
        memset(&hints,0,sizeof(struct addrinfo));
        hints.ai_protocol = IPPROTO_UDP;
        hints.ai_family = AF_INET;
        struct addrinfo * res;
        getaddrinfo(argv[1],"1069",&hints,&res);
        int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        char host_name[128] = {0};
        char serv_name[128] = {0};
        getnameinfo(res->ai_addr,res->ai_addrlen,host_name,128,serv_name,128, NI_NUMERICHOST|NI_NUMERICSERV);
        write(STDOUT_FILENO,host_name,128);
        write(STDOUT_FILENO, "OK\n", 2 );
    }
}

void sendData(int *sd,struct addrinfo * res,char* data,int packetnumber){
    char SendBuf[BufferSize] ={0};
    SendBuf[1]=3;
    SendBuf[2]=packetnumber&0xF0;//Spreading the packet number with MSBs
    SendBuf[3]=packetnumber&0x0F;//Spreading the packet number with LSBs in case the packet number is >127
    sprintf(SendBuf+4,"%s",data);
    sendto(*sd,SendBuf,strlen(data)+4,0,res->ai_addr,res->ai_addrlen);//RRQ sending
}

/*

const char requete[] = "GET / HTTP/1.1\r\nHost: www.perdu.com\r\n\r\n";
char reply[2048]={0};
write(sd,requete,strlen(requete));
int status = read(sd,reply,2048);

printf("%d bytes received : %s\n",status,reply);
*/
