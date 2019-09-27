#!/bin/bash

if test $# -gt 1
then
	echo "Uso: \"$0 directorio\", o \"$0\" para buscar en el directorio actual"
	exit 1
elif test $# -eq 1
then
	if test -d $1
	then
		WDIR=$1
	else
		echo "$1 no existe o no es un directorio"
		exit 2
	fi		
else
	WDIR="./"
fi

find $WDIR -name "[ab]*"  | grep -v '~'

