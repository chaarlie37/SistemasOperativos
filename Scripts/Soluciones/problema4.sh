#! /bin/bash

if test $# -ne 1
then
	echo "Uso: \"$0 nombre_archivo\""
	exit 1
fi

FILE=$1
FOUND=0
for DIR in `echo $PATH | tr ':' '\n'`
do	
	STRING=`find  $DIR -name $FILE` 
	if ! test -z $STRING  
	then
		echo "$FILE está en $STRING"
		FOUND=1	
	fi	 
done

if test $FOUND -eq 0
then
	echo "$FILE no se encuentra en ningún directorio del PATH"
	exit 2
fi

		
