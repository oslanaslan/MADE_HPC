// #include <stdio.h>
#include <iostream>
#include <stdlib.h>
// #include <sys/time.h>
#include <ctime>
#include "matrix.h"

// const size_t N = 1024;

int main()
{
    size_t N;
    int NRuns = 5;
    size_t i, j, k;
    double *runtimes;
    double *A, *B, *C;

    std::cin >> N;

    A = (double *) malloc(N * N * sizeof(double));
    B = (double *) malloc(N * N * sizeof(double));
    C = (double *) malloc(N * N * sizeof(double));
    runtimes = (double *) malloc(NRuns * sizeof(double));

    RandomMatrix(&A[0], N);
    RandomMatrix(&B[0], N);

// ijk ordering
    double average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_ijk(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }

    printf("average runtime ijk %lf seconds\n", average_runtime);
    printf("---------------------------------\n");


// jik ordering
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_jik(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }

    printf("average runtime jik %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
    

// kij ordering
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_kij(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }
    printf("average runtime kij %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
    
// kij ordering naive optimization (useless for -O3)
    average_runtime = 0.0;
    for(int n=0; n<NRuns; n++)
    {
        runtimes[n]=CalcMatMulTime_kij_opt(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n]/NRuns;
    }
    printf("average runtime kij opt %lf seconds\n", average_runtime);
    printf("---------------------------------\n");

    free(A); 
    free(B);
    free(C);
    return 0;
}
