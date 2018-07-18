#!/bin/bash
#!/bin/bash
gid=(`cat /etc/passwd | cut -d ":" -f 4`)
user_name=(`cat /etc/passwd | cut -d ":" -f 1`)
count=0;
for((i =0 ;i<${#gid[@]};i++));do
    if [[ ${gid[$i]} -gt 1000   ]];then

        count=$[${count}+1 ];
    fi
done;

last_name=`last | tr -s " " " " | cut -d " " -f 1 | head -n -1`
top=(` last | tr -s " " " " | cut -d " " -f 1 | head -n -2 | sort -n | uniq -c | sort -r | tr -s " " " " | cut -d " " -f 3 `)

su_group=`grep sudo /etc/group |cut -d ":" -f 4`
sudoers=(`cat /etc/sudoers | grep "ALL=(ALL:ALL) ALL" | head -n -1 | cut -d " " -f 1`) 
log_name=(`w | tail -n +3 | tr -s " " " " | cut -d " " -f 1`)
log_ip=(`w | tail -n +3 | tr -s " " " " | cut -d " " -f 3 `)
log_tty=(`w | tail -n +3 | tr -s " " " " | cut -d " " -f 2`)







echo -n ${count} 
echo -n " "
echo -n "["
for((i=0;i<3;i++));do
    echo -n ${top[ $i  ]}
    echo -n " "
done

echo -n "]"

echo -n "["
for((i=0;i<${#user_name[@]};i++));do
    for((j=0;j<${#sudoers[@]};j++));do
       # echo ${user_name[$i]} ${sudoers[$j]}
        if [[ ${user_name[ $i ]} == ${sudoers[ $j ]}  ]];then
            echo -n ${user_name[ $i  ]}" " 
        fi
    done
done 
echo -n ${su_group}
echo -n "]"

echo -n "["
for((i=0;i<${#log_name[@]};i++));do
    echo -n "["
    echo -n ${log_name[$i]}
    echo -n " "
    echo -n ${log_ip[$i]}
    echo -n " "
    echo -n ${log_tty[$i]}
    echo -n "]"
done
echo "]"
