#!/bin/bash
if test $# -eq 0
then
    DIR=$(pwd)
elif test $# -eq 1
then
    DIR=$1
else
    echo "Número de argumentos inválido. Introduzca 1 argumento o ninguno para utilizar el actual." ; exit 1
fi

if ! test -d $DIR
then
    echo "Error. $DIR no es un directorio. Introduzca un directorio válido." ; exit 2
fi

find $DIR -name "[ab]*"  | grep -v "~"

exit $?
