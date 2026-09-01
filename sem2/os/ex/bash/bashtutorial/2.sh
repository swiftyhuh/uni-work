a=$1
b=$2
if [ $a -lt $b ]; then
  echo t: min=$a
else
  echo e: min=$b
fi
