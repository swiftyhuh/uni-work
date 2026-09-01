#!/bin/bash
# Write a bash script that takes as command line arguments pairs consisting of (filename, integer)
# Check if the file size is less than the specified integer
# And also calculate the total size of the files
# ./script.sh file1 100 file2 503

total=0
while test $# -gt 1 ; do
    fname=$1
    num=$2
    if [ -n "${fname}" ] && [ -f "${fname}" ]; then
        fsize=$(du -b $fname | awk '{print $1}')
        if [ $fsize -lt $2 ]; then
            echo "File $fname has size $fsize; smaller than $num"
        else
            echo "File $fname has size $fsize; greater or equal than $num"
        fi
        total=$(($total + $fsize))
    else
       echo "Argument $fname is not a file!"
    fi
    shift 2
done
echo "Total size: $total"