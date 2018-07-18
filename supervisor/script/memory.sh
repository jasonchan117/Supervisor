#!/bin/bash
time=`date -u +"%Y-%m-%d__%H:%M:%S"`
va=(`free -m | head -2 | tail -1 | awk '{print $2,$3,$2/$3}'`)
available=`free -m | head -n 2 | tail -n 1 | tr -s " " "+" | cut -d "+" -f 7`
used=`free -m | head -n 2 | tail -n 1 | tr -s " " "+" | cut -d "+" -f 4`
total=`free -m | head -n 2 | tail -n 1 | tr -s " " "+" | cut -d "+" -f 2`
data=$1
ans=`echo "scale=1;${used}*100/${total}" | bc`
echo ${ans}
MemAvaPrec=`echo "scale=1;$[${va[1]}*100]/${va[0]}" | bc`
NowAva=`echo "scale=1;${MemAvaPrec}*0.8+0.2*${data}" |bc`
echo $date ${va[0]}M ${va[1]}M ${va[2]}% ${NowAva}
echo ${NowAva}
