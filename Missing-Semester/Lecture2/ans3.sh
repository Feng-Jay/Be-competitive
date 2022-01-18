#!/usr/bin/env bash

echo "begin test" > run.log

time=0

while [[ $? -eq 0 ]]; do
    let time++
    echo "failed at $time times" > error.log
    bash ./random.sh 1>>run.log 2>>error.log
done 