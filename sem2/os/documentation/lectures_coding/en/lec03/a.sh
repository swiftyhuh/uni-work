#!/bin/bash

for P in `ps -ef | grep -E -v "^root\>" | awk '{print $2}'| tail -n +2`; do
    T=`ps -o etime $P|tail -n +2`
    if test -z "$T" || echo $T | grep -E -q ".*:.*:"; then
        continue
    fi
    M=`echo $T | sed -E "s/:.*//"`
    S=`echo $T | sed -E "s/.*://"`
    X=`expr $M \* 60 + $S`

    if test $X -gt 1600; then
        echo $P $T $M $S $X
    fi
done
