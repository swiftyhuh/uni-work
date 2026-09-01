#!/bin/bash

ps -e -f|grep -E "^ex|^yz"|awk '{print $1, $2}'| while read U P; do
    echo $U $P
done
