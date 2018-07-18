#!/bin/bash
time=`date -u +"%Y-%m-%d__%H:%M:%S"`
guazai=(` df | grep -v "tmpfs"| tr -s " " "+" | cut -d "+" -f 6 | tail -n +2`)
total=(` df | grep -v "tmpfs" | tr -s " " "+" | cut -d "+" -f 2 | tail -n +2`)
used=(`df | grep -v "tmpfs" | tr -s " " "+" | cut -d "+" -f 4 | tail -n +2`)
total_disk=0
for((i=0;i<${#total[@]};i++));do
    total_disk=$[${total_disk}+${total[ $i ]}];
done
total_used=0
for((i=0;i<${#used[@]};i++));do
    total_used=$[ ${total_used}+${used[ $i ]} ];
done
flag=0
for((i=0;i<${#total[@]};i++));do
    echo ${time} 1 ${guazai[ $i ]} ${total[ $i ]}M ${used[ $i ]}M `echo "scale=1;$[${total[i]}-${used[i]}]*100/${total[i]}" | bc`%
done

echo ${time} 0  ${total_disk}M ${total_used}M `echo "scale=1;$[${total_disk}-${total_used}]*100/${total_disk}" | bc`%
