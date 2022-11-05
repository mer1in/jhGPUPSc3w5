#!/bin/bash
echo "Monitor started"
WHAT='./run.sh'

while [[ true ]]
do
    echo -n .
    git pull -r &>/dev/null
    echo -n .
    chsum2=`git log -1 --oneline`
    if [[ $chsum1 != $chsum2 ]]
    then
        echo "Got changes, rebuild"
        chsum1=$chsum2
        echo $WHAT
        (echo "$WHAT" | bash -)
        echo $chsum1
    fi
    echo -n .
    sleep 2
done
