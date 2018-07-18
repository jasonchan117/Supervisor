#!/bin/bash
declare -a mark=(`seq 1 1000000`)
for((i=1;i<100000;i++));do 
    mark[ $i ]=0;
done
fl=1
j=0
mark_pid=-1
mark_info=(`ps -axu |tr -s " " " "|tail -n +1 | awk '{if($3>=50||$4>=50) printf("warning:PID:%dOWNER:%sCPU:%dMEM:%d\n",$2,$1,$3,$4);}'`)
mark_pid=(`ps -axu | tr -s " " " "| tail -n +1 | awk '{if($3>=50||$4>=50) printf("%d\n",$2);}'`)
    
if [[  ${mark_pid[0]} -eq -1 ]];then
        fl=0 
elif [[ -z "$mark_info[0]"  ]];then
        fl=0
else
    for((i=0;i<${#mark_pid[@]};i++));do
        if [[ ${mark[ ${mark_pid[ $i  ]}  ]} -eq 0  ]];then 
            date=`date -u +"%Y-%m-%d__%H:%M:%S"`
            echo ${date} ${mark_info[ $i ]}
            mark[ ${mark_pid[ $i ]}  ]=1;    
            flag=1
            echo testing
            for((k=1;k<=5;k++));do
                re_check=0
                re_check=`ps -axu | tr -s " " " " | tail -n +1 | awk '{if(($2 == mark_pid[$i])&&($3 >= 50||$4 >= 50)) printf("%d",$2)}'`
                if [[ ${re_check} == ${mark_pid[ $i ]}  ]];then
                    flag=0;
                    break;
                fi
                sleep 0.5
            done
        
            if [[ ${flag} -eq 1  ]];then
                echo PID:${mark_pid[ $i ]} is a bad processing
                echo ${mark_pid[ $i  ]} >> bad.log
            fi
        fi
    done
fi
j=$[ $j + 1  ]



