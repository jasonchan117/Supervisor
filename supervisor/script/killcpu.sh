#! /bin/sh 
# filename killcpu.sh
if [ $# -ne 1  ] ; then
      echo "USAGE: $0 <CPUs>|stop"
        exit 1;
    fi

    stop()
    {
         while read LINE
               do
                       kill -9 $LINE
                           echo "kill $LINE sucessfull"
                             done < pid.txt
                              cat /dev/null > pid.txt

    }

    start()
    {
          echo "u want to cpus is: "$1
            for i in `seq $1`
            do
                  echo -ne " 
                  i=0; 
                  while true
                  do
                      i=i+1; 
                  done" | /bin/sh &
                    pid_array[$i]=$! ;
                done

                for i in "${pid_array[@]}"; do
                      echo 'pid is: ' $i ';';
                        echo $i >> pid.txt
                    done

    }

    case $1 in
           stop)
                   stop
                     ;;
                        *)
                               start $1
                               ;;
                       esac
