#!/bin/bash

D=$1

N=0
for F in $D/*.c; do
    K=`grep -E -v "^[ {}]*$" $F |wc -l`
    N=`expr $N + $K`
done
echo $N
