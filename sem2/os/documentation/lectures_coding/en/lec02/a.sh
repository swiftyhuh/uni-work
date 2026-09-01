#!/bin/bash

echo $0
echo $1
echo $9
echo $*
echo $@
echo $#

shift 7
echo $*
echo $#

for A in x y z *.txt `who | awk '{print $1}'` $*; do
    echo $A
done

for A in $*; do
    if test -f $A; then 
        echo $A is a file
    elif test -d $A; then
        echo $A is a directory
    elif echo $A | grep -E -q "^[0-9]+$"; then
        echo $A is a number
    else
        echo asfdliuasfiuahfuh
    fi
done

while read X; do
    echo I read $X
done
