#!/bin/bash

while true; do
    read -p "Enter filename or stop: " file
    if [ "$file" = "stop" ]; then
        echo "M am oprit champ"
        exit 1
    elif [ -f "$file" ]; then
        if file $file | grep -Eq "text"; then
            echo "File: $file - Words on first line: $(head -1 $file | wc -w)"
        fi
    fi
done
