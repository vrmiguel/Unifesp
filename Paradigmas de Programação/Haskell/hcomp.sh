#!/bin/bash 
# Vinícius Rodrigues Miguel
# github.com/vrmiguel/Unifesp  
# Usage: hcomp {filename}.hs

set -e

if [ $# -ne 1 ]; # Número de argumentos deve ser 1.
    then echo "Usage: hcomp {filename}.hs"; exit 1;
fi

h='hcomp_temporary_folder_000'

if [ -d $h ];
    then rm -rf $h
fi

mkdir $h

ghc $1 -outputdir $h        # Compilando 

filename=$(basename -- "$1")  
extension="${filename##*.}"
filename="${filename%.*}"      # Obtendo nome do arquivo executável

rm -rf $h       # Deletando arquivos temporário

./$filename                 
