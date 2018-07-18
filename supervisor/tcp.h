/*************************************************************************
	> File Name: tcp.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月10日 星期日 17时00分15秒
 ************************************************************************/

#ifndef _TCP_H
#define _TCP_H


int socket_create(int port){
    int socket_num=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socket_num==-1){
        perror("socket_create");
        return -1;
            
    }
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int mark=bind(socket_num,(struct sockaddr *)&addr,sizeof(addr));
    if(mark==-1){
        perror("bind");
        return -1;
            
    }
    mark=listen(socket_num,10);
    if(mark==-1){
        perror("listen");
        return -1;
            
    }
    return socket_num;
}
int socket_connect(int port,char *host){
    
    int sockfd;
    struct sockaddr_in dest_addr;
    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0){
        perror("created");
        return -1;
            
    }
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if(connect(sockfd,(struct sockaddr *)&dest_addr,sizeof(dest_addr))<0){
        perror("connect");
        return -1;
            
    }
    return sockfd;
}

#endif
