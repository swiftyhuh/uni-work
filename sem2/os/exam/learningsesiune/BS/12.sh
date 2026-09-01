#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Provide at least one argument"
    exit 1
fi

if [ ! -d $1 ]; then
    echo "$1 its not a folder"
    exit 1
fi

old='ls -l "$1"'

while true; do
    sleep 1
    new='ls -l "$1"'
    if [ "$old" != "$new" ]; then
        echo "S o schimbat tulai"
        break
    fi
done


