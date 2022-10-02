#!/bin/bash

n_arr=( 500 512 1000 1024 2000 2048 )
touch time_test_results.txt

for i in ${n_arr[@]}; do
    echo "Testing matrix size $i x $i"
    echo "Matrix size: $i x $i" >> time_test_results.txt
    echo $i | ./bin/x64/Release/MatrixMul >> time_test_results.txt
done