#!/bin/bash

echo "nr arguments: $#"
echo "arguments: $@"
echo "arg: ${10}"

# this is one way to iterate through the command line arguments
#for x in "$@"; do
#    echo "$x"
#done

# this is another way to iterate through the command line arguments
# the i variable is not needed to iterate, but it is here to show how incrementing works in bash
i=0
while test $# -gt 0; do
    # arithmetic operations
    i=$((i+1))
    echo "Arg nr $i = $1"
    shift
done

# command substitution, which means "make the command(s) return whatever would be printed at stdout
a=`ps -ef | awk 'NR > 1 {print $1}' | sort | uniq -c | sort -n -r`

echo "Output: $a"

# assigning a variable -> do not put spaces around the "=" sign
b=5
c="something"
