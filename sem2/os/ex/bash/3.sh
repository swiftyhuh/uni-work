#!/bin/bash
dir=$1
size=$2

find $dir -type f | while read F; do
  N=$(ls -l $F | awk '{print $5}')
  if [ $N -gt $size ]; then
    echo $F
  fi
done
