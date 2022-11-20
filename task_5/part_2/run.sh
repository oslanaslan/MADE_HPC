#!/bin/bash
NUM_PROC=4
STATE_LEN=100
ITER_CNT=1000

mkdir results
mpic++ worker.h worker.cpp main.cpp
mpirun --allow-run-as-root -n $NUM_PROC ./a.out $STATE_LEN $ITER_CNT >> rule_res.csv
python3 union_res.py
