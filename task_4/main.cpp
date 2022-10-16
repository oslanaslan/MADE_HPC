#include <iostream>
#include <matrix.h>
#include <chrono>

using high_res_clock = std::chrono::high_resolution_clock;

/**
 * @brief Generate random matrx of size n x m
 * 
 * @param n - number of rows
 * @param m - number of cols
 * @return Matrix 
 */
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

/**
 * @brief Test raising to the power of n on a randomly
 * generated matrix
 */
void test_on_random_matrix() {
    int n, m;

    std::cout << "Random matrix size: ";
    std::cin >> n;
    std::cout << "N: ";
    std::cin >> m;
    Matrix a = random_matrix(n, n);
    auto st = high_res_clock::now();
    Matrix c = a^m;
    auto et = high_res_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(et - st).count();
    std::cout << elapsed << " millisec" << std::endl;
}

/**
 * @brief Read matrix from file and raise to the power of n
 * As test file can be used file data/moscow_subway_mat.txt 
 */
void test_on_matrix_from_file() {
    int n;
    std::string input_file, output_file;
    std::cout << "Input file path: ";
    std::cin >> input_file;
    std::cout << "Output file path: ";
    std::cin >> output_file;
    std::cout << "n: ";
    std::cin >> n;
    Matrix a(input_file);
    auto st = high_res_clock::now();
    Matrix c = a^n;
    c.to_file(output_file);
    auto et = high_res_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(et - st).count();
    std::cout << elapsed << " millisec" << std::endl;
}

int main() {
    std::cout << "=== Random matrix test ===" << std::endl;
    test_on_random_matrix();
    std::cout << "=== Test on matrix from file ===" << std::endl;
    test_on_matrix_from_file();
}
