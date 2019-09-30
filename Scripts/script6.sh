#!/bin/bash
if test $# -ne 1
then
    echo "Número de argumentos incorrecto. Debe introducir uno solo."
    exit 1
fi
if ! test -e $1  || ! test -f $1  || ! test -f $1
then
    echo "$1 no es un fichero, no existe, está vacío o no tiene terminación .tgz. El argumento debe ser un fichero con terminación .tgz. y contener datos"
    exit 2;
fi
if test -z `echo $1 | grep "\.tgz$"`
then
    echo "$1 no tiene terminación .tgz" ; exit 3
fi

DIR=`mktemp -d`

if test -n `echo $1 | grep "^/"`
then
    FICHERO=$1
else
    DIRORIGINAL=`pwd`"/"
    FICHERO=$DIRORIGINAL$1
fi

cd $DIR
tar -xvzf $FICHERO
for FICH in `find $DIR -type f -size -10M -print0 | xargs -0 rm`
do
    rm -f $FICH
done

rm -f $FICHERO
tar -cvzf $FICHERO `ls`
exit $?
