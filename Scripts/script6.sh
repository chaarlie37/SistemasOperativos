#!/bin/bash
if test $# -ne 1
then
    echo "Número de argumentos incorrecto. Debe introducir uno solo."
    exit 1
fi
if ! test -e $1  || ! test -f $1  || ! test -f $1
then
    echo "$1 no es un fichero, no existe o está vacío. El argumento debe ser un fichero con terminación .tgz. y contener datos"
    exit 2;
fi

DIR=`mktemp -d`
DIRORIGINAL=`pwd`"/"
FICHERO=$DIRORIGINAL$1
cd $DIR
tar xvzf $FICHERO
for FICH in `find $DIR -type f -size -500k -print0 | xargs -0 rm`
do
    rm -f $FICH
done

rm -f $FICHERO
tar cvzf $FICHERO `ls`
exit $?
