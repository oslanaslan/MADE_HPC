#!/bin/bash

# check if subdirectory "Linux" exists in present directory.
# If yes, print message "course".
# If no, print message "very easy" and create the "Linux" directory

parent="."
child="Linux"

path=$parent/$child

if [ -d "$path" ]; then
    echo "course"
else
    echo "very easy"
    mkdir "Linux"
fi
