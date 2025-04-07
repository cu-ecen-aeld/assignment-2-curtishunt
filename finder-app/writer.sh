#!/bin/bash

# Check number of inputs
if [ "$#" -ne 2 ]; then
    echo "ERROR usage is: writer.sh <path to file/filename> <string to be written>"
    exit 1
fi

# Assign args
writefile=$1
writestr=$2

path=$(dirname "$writefile")

mkdir -p "$path"
#check exit status of mkdir command
if [ $? -ne 0 ]; then
    echo "ERROR: failed to create directory."
    exit 1
fi

touch "$writefile"
#check exit status of touch command
if [ $? -ne 0 ]; then
    echo "ERROR: failed to create file."
    exit 1
fi

echo "$writestr" >| "$writefile"

#check exit status of echo command
if [ $? -ne 0 ]; then
    echo "ERROR: failed to write to file."
    exit 1
fi

exit 0
