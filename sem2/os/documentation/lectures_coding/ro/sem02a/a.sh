#!/bin/bash

T=0
for F in `find git/ -type f -name "*.diff"`; do
    N=`grep -E -v "^[ \t{}]*$" $F | wc -l`
    T=`expr $T + $N`
done
echo $T
