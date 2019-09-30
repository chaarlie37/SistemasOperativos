#!/bin/bash
if test $# -gt 1
then
    echo "El número de argumentos debe ser 1 o ninguno."
    exit 1
fi
if test $# -eq 1
then
    if ! test -d $1 || ! test -e $1
    then
        DIR=$1
    else
        echo "$1 no es un directorio o no existe."
        exit 2
else
    DIR=`pwd`
fi

for FICH in `find $DIR -name "*3*\.txt"`
do
    mv $FICH `sed s/txt/md/ <<< $FICH`
done
