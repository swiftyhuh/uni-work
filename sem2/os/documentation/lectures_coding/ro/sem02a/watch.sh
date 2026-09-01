#!/bin/bash

D=$1
F=.watch
STATE=""
while true; do
    ST=""

    find $D > $F
    while read X; do
        if [ -d "$X" ]; then
            META=`ls -ld "$X" | sha1sum`
            DATA=`ls -l "$X" | sha1sum`
        elif [ -f "$X" ]; then
            META=`ls -l "$X" | sha1sum`
            DATA=`cat "$X" | sha1sum`
        fi
        ST="$ST\n$META $DATA"
    done < $F

    if [ -n "$STATE" ] && [ "$STATE" != "$ST" ]; then
        echo "S-a modificat ceva"
    fi
    if [ -z "$STATE" ]; then
        echo "A trecut o prima tura"
    fi
    STATE=$ST

    sleep 1
done
