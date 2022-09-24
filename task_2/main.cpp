#include <iostream>
#include <matrix.h>
#include <chrono>

using high_res_clock = std::chrono::high_resolution_clock;

Matrix random_matrix(size_t n, size_t m) {
    Matrix matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            double a = static_cast<double>(rand());
            double b = static_cast<double>(rand()) + 1;

            matrix[i][j] = a / b;
        }
    }

    return matrix;
}

int main() {
    size_t n, m;

    std::cin >> n >> m;
    Matrix a = random_matrix(n, m);
    Matrix b = random_matrix(m, n);
    auto st = high_res_clock::now();
    Matrix c = a * b;
    auto et = high_res_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(et - st).count();
    std::cout << elapsed << " millisec" << std::endl;
}
