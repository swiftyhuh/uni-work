#!/bin/bash
Please
if [ $# -eq 0 ]; then
    echo "Please provide at least one argument"
    exit 1
fi

if [ ! -d $1 ]; then
    echo "Please provide one directory"
    exit 1
fi

sum=0
for f in $(ls $1); do
    if [ -f "$1/$f" ]; then
        size=$(du -b "$1/$f" | awk '{print $1}')
        echo "File: $f - Size: $size"
        sum=$((sum+size))
    fi
done
echo "Total size from folder $1 is $sum"
