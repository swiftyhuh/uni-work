#!/bin/bash
# Write a bash script that prints all the processes belonging to a specified user
# ./2.sh username

# the easy way
u=$1
ps -ef | grep -E "^$u"

# the very weird and complicated way
# also how to make bash iterate over lines with IFS and for
tmp="$IFS"
IFS=$'\n'
for line in $(ps -ef); do
    user=$(echo "$line" | awk '{print $1}')
    if [ "$user" = "$u" ]; then
        echo $line
    fi
done
IFS="$tmp"
