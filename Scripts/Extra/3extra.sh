#!/bin/bash
cd $HOME
mkdir CarpetaGenerica #Creo una carpeta en $HOME que mi distro no tiene escritorio
cd CarpetaGenerica
for VAR in `seq 1 40`
do
    touch $VAR".txt"
done
