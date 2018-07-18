#!/bin/bash
date=`date -u +"%Y-%m-%d__%H:%M:%S"`
hostname=`cat /etc/hostname`
os=`uname -v | tr -s " " " " | cut -d " " -f 1`
nihe=`uname -r`
runingtime=`uptime -p | tr -s " " "_" `
upload=` uptime | cut -d "," -f 4-6 | cut -d ":" -f 2 | cut -d "," -f 1-3 | tr -s "," " "`
tempo=`cat /sys/class/thermal/thermal_zone0/temp`
temprature=`echo ${tempo}/1000 | bc`
total=`df | grep -v "tmpfs" | tr -s " " "+" | cut -d "+" -f 2 | tail -n +2`
disk_total=0
for i in ${total};do
    disk_total=$[${disk_total}+$i]
done
canuse=`df | grep -v "tmpfs" | tr -s " " "+" | cut -d "+" -f 4 | tail -n +2`
disk_canuse=0
for i in ${canuse};do
    disk_canuse=$[${disk_canuse}+$i]
done
mem_total=` free | tail -n +2 | head -n -1 | tr -s " " " " | cut -d " " -f 2`
mem_used=`free | tail -n +2 | head -n -1 | tr -s " " " " | cut -d " " -f 3 `


mem_prot=`echo "scale=0;100*${mem_used}/${mem_total}" | bc`
disk_prot=`echo "scale=0;100* (${disk_total}-${disk_canuse})/${disk_total}" | bc`
if [[ ${temprature} -lt 50 ]];then
    cpu_level=normal

elif [[ ${temprature} -lt 70  ]];then
    cpu_level=note
    else
        cpu_level=warning
fi
if [[ ${disk_prot} -lt 70 ]];then
    disk_level=normal
elif [[ ${disk_prot}  -lt 90 ]];then 
    disk_level=note
else 
    disk_level=warning
fi

if [[ ${mem_prot} -lt 70  ]]; then 
    mem_level=normal
elif [[ ${mem_prot} -lt 80  ]];then 
    mem_level=note
else
    mem_level=warning
fi

echo ${date} ${hostname} ${os} ${hihe} ${runingtime} ${upload} ${disk_total} ${disk_prot}% ${mem_total} ${mem_prot}% ${temprature} ${disk_level} ${mem_level} ${cpu_level}
