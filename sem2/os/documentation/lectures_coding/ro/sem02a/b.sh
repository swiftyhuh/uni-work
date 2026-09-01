#!/bin/bash

find git/ -type f -name "*.[ch]" > list
T=0
while read F; do
    N=`grep -E -v "^[ \t{}]*$" "$F" | wc -l`
    T=`expr $T + $N`
done < list
echo $T
