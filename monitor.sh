#!/bin/bash
echo "Monitor started"
WHAT='./run.sh'

while [[ true ]]
do
    git checkout -- .
    git pull -r &>/dev/null
    chsum2=`git log -1 --oneline`
    if [[ $chsum1 != $chsum2 ]]
    then
        echo "Got changes, rebuild"
        chsum1=$chsum2
        (echo "$WHAT" | bash -)
        echo $chsum1
    fi
    sleep 2
    echo -n .
done
