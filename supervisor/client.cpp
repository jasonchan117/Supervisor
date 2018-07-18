/*************************************************************************
	> File Name: client.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月22日 星期五 18时59分36秒
 ************************************************************************/

#include<iostream>
#include<arpa/inet.h>
#include<ctype.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/file.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<time.h>
#include<unistd.h>
#include<stdarg.h>
#include<iostream>
#include"tcp.h"
#include<stdlib.h>
#include"ado.h"
#include"bdo.h"

int main(){
    int ac_socket;
    while(1){
        int long_port=get_port(2);
        int l_lis;
        printf("%d\n",long_port);
        if((l_lis=socket_create(long_port))<0) {perror("binding long port"); return -1;}
        
        puts("waiting for connecting");
        if((ac_socket=accept(l_lis,(struct sockaddr *)NULL,NULL))<0){perror("accept");return -1;}//creating long connect
        while(1){
            char stat_num[10]={0};
            memset(stat_num,0,sizeof(stat_num));
            int recv_statnum;
            if((recv_statnum=recv(ac_socket,stat_num,80,0))<0){perror("recv stat num");return -1;}
        
            if(strcmp(stat_num,"-1")==0) break;
            puts("stat_num have recv");
            puts(stat_num);     
            while(strcmp(stat_num,"101")!=0&&strcmp(stat_num,"201")&&strcmp(stat_num,"301")!=0&&strcmp(stat_num,"401")!=0&&strcmp(stat_num,"501")!=0&&strcmp(stat_num,"601")!=0){//recv stat_num
            memset(stat_num,0,sizeof(stat_num));
                                                                                                                puts("rerecv");
                if((recv_statnum=recv(ac_socket,stat_num,80,0))<0){perror("recheck");return -1;}
            }
            FILE *fp;
            char ack[10]={0};
            memset(ack,0,sizeof(ack));
            get_command_msg(fp,stat_num,ack);//get command msg and ack code
            puts("ack have created");
            puts(ack);
            int send_ack;
            if((send_ack=send(ac_socket,ack,50,0))<0) {perror("send ack");return -1;}//send ack
            char send_msg[1000]={0};
            puts("ack have sended");
            
            int short_port=get_port(1);
            int s_lis;
            int s_socket;
            if((s_lis=socket_create(short_port))<0) {perror("binding short port"); return -1;}
            puts("waiting for short connecting");
            if((s_socket=accept(s_lis,(struct sockaddr *)NULL,NULL))<0) {perror("short connect");return -1;}//do short_connect
            puts("short have connected");
            
            while((fgets(send_msg,sizeof(send_msg)-1,fp))){//send command to master
                int msg;
                puts(send_msg);
                if((msg=send(s_socket,send_msg,strlen(send_msg),0))<0) {perror("send msg");return -1;}
                memset(send_msg,0,sizeof(send_msg));
            }
            pclose(fp);
            close(s_socket);
            close(s_lis);
        }
        close(ac_socket);
        close(l_lis);
    }
    return 0;
}
