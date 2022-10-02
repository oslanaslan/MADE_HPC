#!/bin/bash

if [ ! -f Makefile ]; then
    premake5 gmake
fi

make config=release_x64

# tests 500, 512, 1000, 1024, 2000, 2048

for test in 500 512 1000 1024 2000 2048; do
    res=$(echo "$test $test" | ./bin/x64/Release/MatrixMul)
    echo "Test $test x $test: $res"
done
