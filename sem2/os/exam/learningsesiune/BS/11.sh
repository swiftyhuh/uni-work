#!/bin/bash

if [ -z $@ ]; then
    echo "SUgi pula ba"
    exit 1
fi

for f in $@; do
    if file $f | grep -Eq "C source"; then
        grep -E "#include" $f >> salut
    fi
done
