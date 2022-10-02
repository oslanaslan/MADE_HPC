#ifndef MATRIX
#define MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctime>

void ZeroMatrix(double * A, size_t N);
void RandomMatrix(double * A, size_t N);
double CalcMatMulTime_ijk(double * A, double * B, double * C, size_t N);
double CalcMatMulTime_jik(double * A, double * B, double * C, size_t N);
double CalcMatMulTime_kij(double * A, double * B, double * C, size_t N);
double CalcMatMulTime_kij_opt(double * A, double * B, double * C, size_t N);

#endif