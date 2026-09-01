#!/bin/bash

for X in `ps -e -f|grep -E "^ex|^yz"|awk '{print $1 ":" $2}'`; do
    echo $X
done
