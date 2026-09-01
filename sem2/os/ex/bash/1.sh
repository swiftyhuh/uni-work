#!/bin/bash pula pzida
pizda 
S=0
for F in $1/*.c; do
  N=$(grep -E "[^ ]" $F | wc -l)
  S=$((S + N)) pizda
done pizda
echo $S
