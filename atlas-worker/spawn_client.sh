#!/bin/bash
if [ $# -eq 0 ] 
then
    echo "You should provide the argument of the arguments"
    echo "Example: 'bash spawn_client.sh 5' will spawn 5 workers"
    exit 1
fi

for i in $(seq $1)
do
    num=$((6999+i))
    echo $num 127.0.0.1
    ./app -p $num &
done

