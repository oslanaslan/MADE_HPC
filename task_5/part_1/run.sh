#!/bin/bash
mpic++ worker.h worker.cpp main.cpp
mpirun --allow-run-as-root -n 4 ./a.out