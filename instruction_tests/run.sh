#! /bin/bash

echo "l \"$1.hex\"" > $1.run
echo "b 0" >> $1.run
echo ". 1000" >> $1.run
echo "\$2" >> $1.run

~/SVN/a1608897/2016/s1/ca/mipsim/mipsim $2 < $1.run

rm -f $1.run
