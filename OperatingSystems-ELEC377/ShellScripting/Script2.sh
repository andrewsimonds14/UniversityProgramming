filePath=$1

if [ -z "$filePath" ]; then
    path="."
fi

echo "Main files:"

isMain=false

for f in `find $filePath -type f`; 
do
    fullPath=`readlink -f $f`
    if ((`grep -c "^int main" $f` > 0)); then
        isMain=true
        FPRINTF_CTR=`grep -c "fprintf" $f`
        PRINTF_CTR=$(( `grep -c "printf" $f` - $FPRINTF_CTR))
        printf "%s:%d.%d\n" $fullPath $PRINTF_CTR $FPRINTF_CTR
    fi

done

if [ "$isMain" = false ]; 
then
    echo "No main file found"
fi

echo "Module files:"

isModule=false

for f in `find $filePath -type f`; 
do
    fullPath=`readlink -f $f`
    if ((`grep -c "^int init_module" $f` > 0)); then
        isModule=true
        kLines=`grep -n "printk" $f | cut -d : -f 1 | tr '\n' ','`
        kLines=${lineNumbers%?}
        printf "%s:%s\n" $fullPath $kLines
    fi

done

if [ "$isModule" = false ]; 
then
    echo "No module file found"
fi


echo "Other files:"

isOther=false

for f in `find $filePath -type f`; 
do
    fullPath=`readlink -f $f`
    if ((`grep -c "^int main" $f` == 0)); then
        if (( `grep -c "^int init_module" $f` == 0)); then
            isOther=true
            printf "%s\n" $fullPath
        fi
    fi

done

if [ "$isOther" = false ]; 
then
    echo "No other file found"
fi
