#!/bin/bash

D=$1

N=0
find git/ -type f -name "*.c" -or -name "*.h" > .files
while read F; do
    K=`grep -E -v "^[ {\t}]*$" "$F" |wc -l`
    N=`expr $N + $K`
done < .files
echo $N
