#!/bin/bash

D=$1

STATE=""
while true; do
    ST=""
    find $D > .files
    while read F; do
        if test -d "$F"; then
            C=`ls -l "$F" | sha1sum`
            M=`ls -ld "$F" | sha1sum`
        elif [ -f "$F" ]; then
            C=`cat "$F" | sha1sum`
            M=`ls -l "$F" | sha1sum`
        fi
        ST="$ST\n$M $C"
    done < .files
    ST=`echo $ST | sha1sum`

    if test -z "$STATE"; then
        echo "s-a facut prima stare"
    fi

    if [ -n "$STATE" ] && [ $STATE != "$ST" ]; then
        echo "s-a schimbat ceva"
    fi
    STATE="$ST"
    sleep 1
done
