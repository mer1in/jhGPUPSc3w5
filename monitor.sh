#!/bin/bash
echo "Monitor started"
WHAT='./run.sh'

while [[ true ]]
do
    echo -n /
    git pull -r &>/dev/null
    chsum2=`find . -type d \( -path ./ffmpeg/out -o -path ./ffmpeg/my \) -prune -o \
        -type f ! -name "\.*\.sw*" -exec md5sum {} \;`
#    chsum2=`find . -type f ! -name "\.*\.sw*" -exec md5sum {} \;`
    if [[ $chsum1 != $chsum2 ]]
    then
        echo "Got changes, rebuild"
        chsum1=$chsum2
        echo $WHAT
        (echo "$WHAT" | bash -)
    fi
    echo -n \
    sleep 2
done
