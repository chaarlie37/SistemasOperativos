#!/bin/bash
if ! test $# -eq 1
then
    echo "Numero de argumentos inválido." ; exit 1
fi
if ! test -f $1 && ! test -d $1
then
    echo "$1 no es un fichero o un directorio." ; exit 2
fi

SIZE=`du -s $1 | cut -f1`
echo "$1 ocupa en disco $SIZE KB"
