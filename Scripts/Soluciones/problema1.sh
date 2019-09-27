#!/bin/bash

if test $# -ne 0
then
	echo "Error. Uso: $0"
	exit 1
fi

for FILE in `ls /bin`
do
	if ! test -e "/usr/share/man/man1/$FILE.1.gz"
	then
		echo "$FILE no tiene entrada de manual"
	fi	
done
