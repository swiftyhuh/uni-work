#!/bin/bash

if [ $# -eq 0 ]; then
    echo "SUgi pula ba"
    exit 1
fi

if [ ! -d $1 ]; then
    echo "da ba un directory"
    exit 1
fi

total=0
for f in $(ls "$1" | grep -E "\.c$"); do
    nr_lines=$(grep -Evc "^[[:space:]]*$" "$1/$f")
    total=$((total+nr_lines))
done
echo "total size $total"
