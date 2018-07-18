/*************************************************************************
	> File Name: master.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月13日 星期三 19时28分38秒
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
#include "bdo.h"
//101 require cpu 100 ack
//201 require disk 200 ack
//301 require memory 300 ack
//401 require sysprofile 400 ack
//501 require usr 500 ack
//601 require badProcessing 600 ack
int main(){
        
        int ba_num=1;
        int stat_num;
        char stat_msg[5]={0};
        char recv_num[5]={0};
        char need_num[5]={0};
        char recv_msg[5]={0};
        char long_ip[20]={0};
        get_ip(long_ip);
        int long_port=get_port(2); 

        int long_socket;
        puts("connecting");
        if((long_socket=socket_connect(long_port,long_ip))<0){perror("connect long");return -1;}//long connect
        puts("have connected");
        for(int i=1;i<=6;i++){
            FILE *fp;
            memset(need_num,0,sizeof(need_num));
            memset(recv_msg,0,sizeof(recv_msg));
            memset(recv_num,0,sizeof(recv_num));
            memset(stat_msg,0,sizeof(stat_msg));

            stat_num=ba_num+i*100;//create stat_num 

            char log_path[100]={0};//find log file
            memset(log_path,0,sizeof(log_path));
            get_log(log_path);
            
            if(stat_num==101) fp=fopen("./log/cpu.log","w+");//open log file
            else if(stat_num==201) fp=fopen("./log/disk.log","w+");
            else if(stat_num==301) fp=fopen("./log/memory.log","w+");
            else if(stat_num==401) fp=fopen("./log/sys.log","w+");
            else if(stat_num==501) fp=fopen("./log/usr.log","w+");
            else if(stat_num==601) fp=fopen("./log/badp.log","w+");
            to_string(stat_msg,stat_num);//create stat_num
            puts(stat_msg);
            
            if(send(long_socket,stat_msg,strlen(stat_msg),0)<0){perror("send stat_num");return -1;}//send stat num
            memset(recv_num,0,sizeof(recv_num));
        
            if(recv(long_socket,recv_num,40,0)<0){perror("recv num");return -1;}//recv ack
            puts("ack have receieved");
            puts(recv_num);
            to_string(need_num,stat_num-1);
            puts("the num needed is");
            puts(need_num);
            while(strcmp(recv_num,need_num)!=0){//rerecv ack
                memset(recv_num,0,sizeof(recv_num));
                if(recv(long_socket,recv_num,40,0)<0){
                    perror("double recv");
                    return -1;
                }    
            }
            char ip[30]={0};
            memset(ip,0,sizeof(ip));
            get_ip(ip);
            int port=get_port(1);
            int socket;
            puts("short connecting");
            if((socket=socket_connect(port,ip))<0) {perror("data connect");return -1;}
            memset(recv_msg,0,sizeof(recv_msg));
            int s;
            while((s=recv(socket,recv_msg,1000,0))>0){//recv msi
                fprintf(fp,"%s\n",recv_msg);
                puts(recv_msg);
                memset(recv_msg,0,sizeof(recv_msg));
            }
            fclose(fp);//close file
            close(socket);//close socket
        }
        char log_out[]="-1";
        if(send(long_socket,log_out,strlen(log_out),0)<0) {perror("send logout signal"); return -1;}
        close(long_socket);
    return 0;
}




