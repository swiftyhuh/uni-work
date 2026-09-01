#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Please provide at least 2 arguments"
    exit 1
fi

if [ $(($# % 2)) -eq 1 ]; then
    echo "you must provide an even number of arguments"
    exit 1
fi

while [ $# -gt 1 ]; do
    file=$1
    word=$2

    if [ ! -f $file ]; then
        echo "$file its not a file"
    else
        count=$(grep -Eo "\<$word\>" $file | wc -l)
        if [ $count -ge 3 ]; then
            echo "Word $word appears $count times in file $file"
        fi
    fi
    shift 2
done


