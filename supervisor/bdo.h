/*************************************************************************
	> File Name: bdo.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月22日 星期五 19时09分38秒
 ************************************************************************/

#ifndef _BDO_H
#define _BDO_H






#define CONF_PATH "./conf/master.conf"
#define KEY_IP "master"
#define KEY_PORT "client_port"
#define KEY_MPORT "master_port"
#define MAX_CONNECT "finish"
#define LOG_PATH "log_path"

int msg_type(char *c){
    if(strcmp(c,"101")==0) return 1;
    if(strcmp(c,"201")==0) return 2;
    if(strcmp(c,"301")==0) return 3;
    if(strcmp(c,"401")==0) return 4;
    if(strcmp(c,"501")==0) return 5;
    if(strcmp(c,"601")==0) return 6;
}



int get_command_msg(FILE *fp,char *stat_num,char *ack){


                
    memset(ack,0,sizeof(ack));
    puts(stat_num);            
    switch(msg_type(stat_num)){
        case 1:{
            strcat(ack,"100");
            puts("hhhhhhh");
            fp=popen("bash ./script/cpu.sh","r");
            break;                
        }
        case 2:{
            strcat(ack,"200");
            fp=popen("bash ./script/disk.sh","r");
            break;
                            
        }
        case 3:{
            strcat(ack,"300");
            fp=popen("bash ./script/memory.sh","r");
            break;
                            
        }
        case 4:{
            strcat(ack,"400");
            fp=popen("bash ./script/sysprofile.sh","r");
            break;
                            
        }
        case 5:{
            strcat(ack,"500");
            fp=popen("bash ./script/usr.sh","r");
            break;                
        }
        case 6:{
            strcat(ack,"600");
            fp=popen("bash ./script/badProcessing.sh","r");
            break;                
        }  
    }
    puts(ack);
    return 1;
}
int get_port(int x){
    char i_port[30]={0};
    int port;
    if(x==2){
        if(!get_conf_value(CONF_PATH,KEY_PORT,i_port)){
            perror("get conf");
            return -1;            
        }
    }
    else if(x==1){
        if(!get_conf_value(CONF_PATH,KEY_MPORT,i_port)){
            perror("get conf");
            return -1;
        }
    }
    port=atoi(i_port);
    return port;
}
int get_ip(char *x){
    char t_ip[30]={0};
    get_conf_value(CONF_PATH,KEY_IP,t_ip);
    for(int i=0;i<strlen(t_ip);i++) x[i]=t_ip[i];
    return 1;

}
int check_ip(char *ip){
    int count=0;
    char temp[30]={0};
    int ind=0;
    for(int i=0;i<strlen(ip);i++){
        if(ip[i]=='.') count++;
        if(count==3&&ip[i]!='.'){
            temp[ind++]=ip[i];
                    
        }
            
    }
    temp[ind]='\0';
    char max_connect[30]={0};
    if(!get_conf_value(CONF_PATH,MAX_CONNECT,max_connect)){
        perror("get conf");
        return -1;            
    }
    int max=atoi(max_connect);
    int num_ip=atoi(temp);
    if(num_ip<=max) return 1;
    else return 0;
}
char *add_ip(char *ip){
    int count=0;
    char temp[30]={0};
    int ind=0;
    for(int i=0;i<strlen(ip);i++){
        if(ip[i]=='.') count++;
        if(count==3&&ip[i]!='.'){
            temp[ind++]=ip[i];        
        }
            
    }
    int sum=atoi(temp);
    sum++;
    int te=sum;
    char tru[10]={0};
    int s=0;
    while(te){
        s++;
        te/=10;
            
    }
    for(int i=s-1;i>=0;i++){
        tru[i]=sum%10;
        sum/=10;
            
    }
    count=0;
    int k=1;
    for(int i=0;i<strlen(ip);i++){
        if(ip[i]=='.') count++;
        if(count==3){
            for(int j=i+1;j<strlen(ip);j++){
                ip[j]=tru[k++];               
            }           
        }        
    }
    return ip;
}

int to_string(char *x,int y){
    int len=0;
    int temp=y;
    while(temp){temp/=10;len++;}
    //len--;
    x[len]='\0';
    while(y){temp=y%10;y/=10;x[len-1]=temp+'0';len--;}
}

int get_log(char *path){
    get_conf_value(CONF_PATH,LOG_PATH,path);
}

#endif
