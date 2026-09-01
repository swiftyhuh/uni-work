#!/bin/bash

for A in $@; do
  echo Arg a: $A
done

for A; do
  echo Argb b: $A
done
