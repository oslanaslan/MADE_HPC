#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// const size_t THR_CNT = 10;
const size_t N = 100;

float dotprod(float* a, float* b, size_t N) {
    int i, tid;
    float sum;

    // omp_set_dynamic(0);
    // omp_set_num_threads(THR_CNT);

    #pragma omp parallel shared(sum) 
    {
        sum = 0.0;

        #pragma omp for reduction(+:sum)
        for (i = 0; i < N; ++i) {
            tid = omp_get_thread_num();
            sum += a[i] * b[i];
            printf("tid = %d i = %d\n", tid, i);
        }
    }

    return sum;
}

int main (int argc, char *argv[]) {
    int i;
    float sum;
    float a[N], b[N];

    for (i = 0; i < N; ++i) {
        a[i] = b[i] = (double)i;
    }

    sum = dotprod(a, b, N);
    printf("Sum = %f\n",sum);

    return 0;
}
