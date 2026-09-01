i=2
while [ $i -lt 7 ]; do
  echo i=$i start
  a=1
  echo a egal $a
  echo sfarsit
  sleep 1
  i=$(($i + 1))
done
