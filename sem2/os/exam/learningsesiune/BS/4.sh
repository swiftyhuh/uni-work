#!/bin/bash

while [ ! $# -eq 0 ]; do
    arg=$1
    if [ -f $arg ]; then
        echo "$arg is a regular file"
    elif [ -d $arg ]; then
        echo "$arg is a directory"
    elif echo $arg | grep -Eq "^[0-9]+$"; then
        echo "$arg is an number"
    else
        echo "$arg is something else"
    fi
    shift
done
