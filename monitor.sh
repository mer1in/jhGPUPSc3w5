#!/bin/bash
echo "Monitor started"
WHAT='./run.sh'

while [[ true ]]
do
    git pull -r >/dev/null
    chsum2=`find . -type f ! -name "\.*\.sw*" -exec md5sum {} \;`
    if [[ $chsum1 != $chsum2 ]]
    then
        chsum1=$chsum2
        echo $WHAT
        (echo "$WHAT" | bash -)
    fi
    echo -n .
    sleep 2
done