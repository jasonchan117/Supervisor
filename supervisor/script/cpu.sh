#!/bin/bash
time=`date -u +"%Y-%m-%d__%H:%M:%S"`
three=` cat /proc/loadavg | head -n 1 | cut -d " " -f 1-3`




kongxian=` cat /proc/stat | head -n 1 | tr -s " " " " | cut -d " " -f 5`
sum=(`cat /proc/stat | head -n 1 | tr -s " " " " | cut -d " " -f 2-11`)
sleep 0.5
kongxian2=`cat /proc/stat | head -n 1 | tr -s " " " " | cut -d " " -f 5`
sum2=(`cat /proc/stat | head -n 1 | tr -s " " " " | cut -d " " -f 2-11 `)

get_sum=0
get_sum2=0
for((i=0;i<${#sum[@]};i++));do
    get_sum=$[${get_sum} + ${sum[$i]}]
done
for((i=0;i<${#sum2[@]};i++));do
    get_sum2=$[${get_sum2}+${sum2[$i]}]
done
#echo ${kongxian} ${kongxian2} ${get_sum} ${get_sum2}

res=`echo "scale=4;(1-((${konxian2}-${kongxian})/(${get_sum2}-${get_sum})))*100" | bc`
res=`printf "%.2f\n" "${res}"`
tempo=`cat /sys/class/thermal/thermal_zone0/temp`
temprature=`echo ${tempo}/1000 | bc`


if [[ ${temprature} -lt 50  ]];then
        cpu_level=normal

elif [[ ${temprature} -lt 70   ]];then
        cpu_level=note
else
    cpu_level=warning
fi



echo $time ${three} ${res}% ${rr} ${cpu_level}


