#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <string>

class Matrix {
    std::vector<std::vector<double>> values;
    size_t n;
    size_t m;

public:

    Matrix(size_t, bool eye = false);
    Matrix(size_t, size_t);
    Matrix(const Matrix&);
    Matrix(Matrix&&);
    Matrix(std::string&);

    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const double);
    Matrix& operator/=(const double);
    Matrix operator^(int);
    friend Matrix operator*(const Matrix&, const Matrix&);
    std::vector<double> operator*=(const std::vector<double>);

    std::pair<size_t, size_t> size() const;
    void to_file(std::string&);

    inline double* operator[] (size_t i) {
        return values[i].data();
    }
};

Matrix operator*(const Matrix&, const Matrix&);
std::istream& operator>>(std::istream&, Matrix&);

#endif