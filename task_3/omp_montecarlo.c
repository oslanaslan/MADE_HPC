#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const size_t THR_CNT = 10;
const size_t SAMPLE_CNT = 1000000;

double get_pi() {
    int circle_cnt = 0;
    double res;

    #pragma omp parallel reduction(+:circle_cnt)
    {
        uint seed = ((unsigned)time(NULL) & 0xFFFFFFF0) | (omp_get_thread_num() + 1);

        for (int i = 0; i < SAMPLE_CNT; i++) {
            double rand_x = (double)rand_r(&seed) / RAND_MAX;
            double rand_y = (double)rand_r(&seed) / RAND_MAX;

            if ((rand_x * rand_x + rand_y * rand_y) < 1.0) {
                circle_cnt++;
            }
        }
    }

    res = (double)circle_cnt / (SAMPLE_CNT * THR_CNT) * 4;

    return res;
}

int main(int argc, char** argv){
    double res;

    omp_set_dynamic(0);
    omp_set_num_threads(THR_CNT);

    res = get_pi();
    printf("%f\n", res);
    
    return 0;
}