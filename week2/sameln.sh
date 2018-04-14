D=$1
for i in `ls -a $D`
do
    if [ -f $i ]
    then
        for j in `ls -a $D`
        do
            if [ -f $j ] && [ $i != $j ]
            then
                cmp -s -- $i $j
                if [ $? -eq 0 ]
                then
                    if [ ${i:0:1} == "." ] && [ ${j:0:1} == "." ]
                    then
                        if [ $(echo $i $j | 
                            awk '$1>$2 {print 1} $1==$2 {print 0} 
                            $1<$2 {print 2}') -eq 0 ]
                        then
                            rm $j
                            ln $i $j
                        else
                            rm $i 
                            ln $j $i
                        fi
                    elif [ ${i:0:1} == "." ] && [ ${j:0:1} != "." ]
                    then
                        rm $j
                        ln $i $j
                    elif [ ${i:0:1} != "." ] && [ ${j:0:1} == "." ]
                    then
                        rm $i
                        ln $j $i
                    else
                        if [ $(echo $i $j | 
                            awk '$1>$2 {print 1} $1==$2 {print 0} 
                            $1<$2 {print 2}') -eq 0 ]
                        then
                            rm $j
                            ln $i $j
                        else
                            rm $i 
                            ln $j $i
                        fi
                    fi
                fi
            fi
        done
    fi
done