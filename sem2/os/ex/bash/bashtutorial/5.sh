#!/bin/bash
if [ $1 = $2 ]; then
  echo true nigga
else
  echo fake nigga
fi
echo

for i in $(ls); do
  echo item: $i
done
echo

for i in $(seq 1 10); do
  echo $i
done
echo

COUNTER=0
while [ $COUNTER -lt 10 ]; do
  echo rares suge $COUNTER puli
  COUNTER=$((COUNTER + 1))
done

COUNTER=20
until [ $COUNTER -lt 10 ]; do
  echo rares mai are de supt $COUNTER puli
  COUNTER=$((COUNTER - 1))
done
echo
