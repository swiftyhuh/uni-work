#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Please provide one argument!"
  exit 1
fi

find "$1" -type f | grep -Ec "\.c$"
