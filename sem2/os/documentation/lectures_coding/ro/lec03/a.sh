#!/bin/bash

for P in `ps -ef | grep -E "^ex|^yz"|awk '{print $2}'`; do
    T=`ps -o etime $P | grep -E -v ELAPSED`
    M=`echo $T | sed -E "s/:.*//"`
    S=`echo $T | sed -E "s/.*://"`
    X=`expr $M \* 60 + $S`
    #echo $P $T $X

    if test $X -gt 2400; then
        echo kill $P
    fi
done
