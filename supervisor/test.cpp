/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月13日 星期三 18时38分12秒
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<iostream>
#include "ado.h"
using namespace std;
int main(){
    char value[100]={0};
    char path[100]="/etc/adduser.conf";
    char name[10]="DSHELL";
    get_conf_value(path,name,value);
    
    puts(value);
    return 0;
}
