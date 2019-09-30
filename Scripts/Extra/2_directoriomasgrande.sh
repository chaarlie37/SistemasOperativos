#!/bin/bash
if test $# -gt 1
then
    echo "Número de argumentos incorrecto. Introduzca un directorio o ninguno para usar el actual."
    exit 1
fi
if test $# -eq 1
then
    if test -d $1
    then
        DIR=$1
    else
        echo "$1 no es un directorio."
        exit 2
    fi
else
    DIR=`pwd`
fi

du -BM -d 1 $DIR | sort -n -k 1
