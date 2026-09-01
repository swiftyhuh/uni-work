#!/bin/bash

if [ -z $1 ]; then
    echo "Please provide one argument"
    exit 1
fi

if [ ! -d $1 ]; then
    echo "Argument must be a directory"
    exit 1
fi

find $1 -type f | sort | uniq -c
