#!/bin/bash

D=$1

N=0
for F in `find git/ -type f -name "*.c" -or -name "*.h"`; do
    K=`grep -E -v "^[ {}]*$" $F |wc -l`
    N=`expr $N + $K`
done
echo $N
