#! /bin/bash

if test $# -gt 1
then
	echo "Uso: \"$0 directorio\", o \"$0\" para buscar en el directorio actual"
	exit 1
elif test $# -eq 1
then
	if test -d $1
	then
		DIR=$1
	else
		echo "$1 no existe o no es un directorio"
		exit 2
	fi		
else
	DIR="./"
fi

# Se realiza un cd para que el listado de ls sobre el directorio sea correcto cuando otro programa como du lo utilice
cd $DIR
# Du recibe los ficheros con los que trabajar como argumentos no por la entrada estandar
du -b `ls` | sort -n -r | head -2

# Otra opcion puede ser utilizar xargs para que convierta la entrada estandar en argumentos del programa
#find $DIR -type f | xargs du -b | sort -n -r | head -2
