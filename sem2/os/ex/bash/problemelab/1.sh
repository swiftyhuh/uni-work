#!/bin/bash

#1.
#if [ $# -lt 1 ]; then
#echo putine argumente bro
#exit 1
#fi
#find $1 -type f | grep -E -c "\.c$"

#2. (not the same solution as in pdf)
# if [ ! -d $1 ]; then
#   echo parameter is not a directory
#   exit 1
# fi
#
# S=0
# for F in $1/*.c; do
#   N=$(grep -E "[^ ]" $F | wc -l)
#   S=$((S + N))
# done
# echo $S

#4.
# while [ ! $# -eq 0 ]; do
#   arg=$1
#   if [ -f $arg ]; then
#     echo $arg its a file
#   elif [ -d $arg ]; then
#     echo $arg its a directory
#   elif echo $arg | grep -E -q "^[0-9]+$"; then
#     echo $arg its a number
#   else
#     echo $arg its something else
#   fi
#   shift
# done
#

#5.
# F=""
# while [ ! -f "$F" ]; do
#   read -p "Enter a string: " F
# done

#6.
# for f in $@; do
#   if [ -f $f ]; then
#     du -b $f
#   fi
# done | sort -n
#
# 7.
# if [ $# -eq 0 ]; then
#   echo Please provide one directory
#   exit 1
# fi
#
# if [ ! -d $1 ]; then
#   echo The argument given its not a directory
#   exit 1
# fi
#
# sum=0
# for f in $(ls $1); do
#   if [ -f "$1/$f" ]; then
#     size=$(du -b "$1/$f" | awk '{print $1}')
#     sum=$((sum + size))
#   fi
# done
# echo $sum
#
# 8.
#
# while true; do
#   read -p "Enter filename or stop: " fn
#   if [ "$fn" = "stop" ]; then
#     exit 1
#   elif [ -f $fn ]; then
#     if file $fn | grep -E -q "text"; then
#       echo $(head -1 $fn | wc -w)
#     fi
#   fi
# done
#
# 9.

# if [ $# -lt 2 ]; then
#   echo pleas provide atleast two arguments
#   exit 1
# fi
#
# if [ $(($# % 2)) -eq 1 ]; then
#   echo you must provide an even number of arguments
#   exit 1
# fi
#
# while [ $# -gt 1 ]; do
#   file=$1
#   word=$2
#
#   if [ ! -f "$file" ]; then
#     echo "name $file is not a file"
#   else
#     count=$(grep -E -o "\<$word\>" "$file" | wc -l)
#     if [ $count -ge 3 ]; then
#       echo word $word appears $count times in file $file
#     fi
#   fi
#   shift 2
# done
#
# 10.
# if [ $# -lt 1 ]; then
#   echo please provide atleast one argument
#   exit 1
# fi
#
# for F in $@; do
#   if [ ! -f $F ]; then
#     echo $F its not a file
#   else
#     du $F
#   fi
# done | sort
#
# 11.
# if [ $# -lt 1 ]; then
#   echo please provide atleast one argument
#   exit 1
# fi
#
# for F in $@; do
#   if $(file $F | grep -E -q "C source"); then
#     grep -E "#include <" $F >>output.txt
#   else
#     echo $F its not a C file
#   fi
# done
#
# 12.
# if [ ! -d "$1" ]; then
#   echo give me a folder
#   exit 1
# fi
#
# old=$(ls -l "$1")
#
# while true; do
#   new=$(ls -l "$1")
#   if [ "$old" != "$new" ]; then
#     echo "something changed in $1"
#     old="$new"
#   fi
#   sleep 2
# done
#
# 13.
# for link in $(find "$1" -type l); do
#   if [ ! -e $link ]; then
#     echo link $link is not valid
#   fi
# done
#
# 14.
# if [ -z "$1" ]; then
#   echo "please provide one argument"
#   exit 1
# fi
#
# if [ ! -d "$1" ]; then
#   echo "argument must be a folder"
#   exit 1
# fi
#
# find "$1" -type f | awk -F/ '{print $NF}' | sort | uniq -c
#
# 15.
# if [ $# -eq 0 ]; then
#   echo "provide at least one name"
#   exit 1
# fi
#
# while true; do
#   for process in $@; do
#     pids=""
#     pids=$(ps -ef | awk '{print $8" "$2' | grep -E "<\$process " | awk '{print $2}')
#     if [ -n "$pids" ]; then
#       kill -9 $pids
#     fi
#   done
#   sleep 3
# done
#
# 17.
#
# if [ $# -eq 0 ] || [ ! -d "$1" ]; then
#   echo "give atleast one valid directory"
#   exit 1
# fi
#
# for f in "$1"/*; do
#   if file -b "$f" | grep -q "C source"; then
#     rm $f
#   fi
# done | ls "$1" | sort
#
# 18.
#
# for f in $(find . -type f -perm -222); do
#   echo $f
#   chmod a-w $f
# done
#
#19.
