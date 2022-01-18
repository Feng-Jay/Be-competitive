#!/usr/bin/env bash

if [[ -d $1 ]]
then 
    echo "Directory exists"
    ls ./$1 -a -l -t -h | head -n 2
else 
    echo "ERROR! Please input correct directory file"
fi