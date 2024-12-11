//
// Created by knn64 on 12/11/24.
//

#ifndef TFTP_H
#define TFTP_H


void cmd_gettftp(int argc,char**);
void cmd_puttftp(int argc,char**);
void sendRRQ(int *sd,struct addrinfo *res,char *file);
void sendData(int *sd,struct addrinfo * res,char* data,int packetnumber);
#endif //TFTP_H
