#!/bin/bash
echo "arg 1: $1"
echo "arg 9: $9"
echo "arg 10: ${10}"

a=-10
if test $a -gt 0; then
  echo "my var: ${a}"
elif test $a -eq 0; then
  echo "this is a big zero"
else
  echo "Woe is me, negatives"
fi

for i in $@; do
  echo "----- $i"
done

while true; do
  echo "Still alive"
  sleep 1
done
