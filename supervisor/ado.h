/*************************************************************************
	> File Name: ado.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月13日 星期三 18时17分55秒
 ************************************************************************/

#ifndef _ADO_H
#define _ADO_H





int get_conf_value(char *pathname,char *key_name,char *value){
    FILE *fp;
    fp=fopen(pathname,"a+");
    if(!fp){
        perror("open file");
        return -1;
    }
    char line[100]={0};
    int flag=0;
    char va[100]={0};
    int k=0;
    char temp[100]={0};
    while((fgets(line,sizeof(line)-1,fp))){
        int ind=0;
        for(int i=0;i<strlen(line);i++){
            if(flag==1){
                va[k++]=line[i];
                if(i==strlen(line)-1){

                    va[k]='\0';
                    for(int i=0;i<strlen(va);i++){
                        value[i]=va[i];
                    }
                    value[k]='\0';
                    
                    return 1;
                }
                continue;
            }
            if(line[i]!='='){
                temp[ind++]=line[i];
            }
            else{
                temp[ind]='\0';
                if(strcmp(temp,key_name)==0){
                    flag=1;
                    memset(temp,0,sizeof(temp));
                    continue;
                }
                else {
                    memset(temp,0,sizeof(temp));
                    break;
                }
            }
        }
        memset(line,0,sizeof(line));
    }
    fclose(fp);
    return 0;
}
#endif
