#!/bin/bash

while [ $# -ge 2 ]; do
  file=$1
  number=$2
  count=0

  while read line; do
    if [ ${#line} -gt $number ]; then
      count=$((count + 1))
    fi
  done <$file

  if [ $count -ge 3 ]; then
    echo "yupppi"
  fi

  shift 2

done
