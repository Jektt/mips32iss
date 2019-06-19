#! /bin/bash

echo "l \"$1.hex\"" > $1.run
echo "b 0" >> $1.run
echo ". 1000" >> $1.run
echo "\$2" >> $1.run

../../mipsim $2 < $1.run

rm -f $1.run
