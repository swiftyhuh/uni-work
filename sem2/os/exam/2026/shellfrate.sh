while read F1 F2; do
  if [ -e "$F1" ] && [ ! -e "$F2" ]; then
    mv "$F1" "$F2"
  fi
done <a.txt

while read F1 F2 F3; do
  if [ -e "$F1" ] && [ -e "$F2" ] && [ ! -e "$F3" ]; then
    cat "$F1" "$F2" >"$F3"
  fi
done <a.txt

while [ $# -gt 0 ]; do
  echo "$1"
  shift
done

# -q make it silent(prints nothing), but if match found exit 0 return true, if not false
if grep -Eq "error" "$F"; then
  echo "Found"
fi
# DO NOT PUT A COMMAND INSIDE [ ].
#
# response = first run - arrival
#  turnaround = completion - arrival
#  waiting  = turnaround - runtime
#

while read F1 F2; do
  if [ -e "$F1" ]; then
    rm "$F2"
  fi
done <a.txt

# formule scheduling sa nu le mai uit
# turnaround = Tcompletion - Tarival
# response = firstrun - arrival
# wait  = turnaround - working


while read F1 F2; do
    if [ -e "$F1" ] && [ ! -e "$F2" ]; then
        mv "$F1" "$F2"
    fi
done < a.txt
