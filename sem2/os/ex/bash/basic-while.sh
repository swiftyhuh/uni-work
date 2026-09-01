#!/bin/bash

while true; do
  read X
  if [ $X == "stop" ]; then
    break
  else
    echo $X
  fi
done
