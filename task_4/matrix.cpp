#include <matrix.h>
#include <ranges>

Matrix::Matrix(size_t n, bool eye) {
    this->n = n;
    this->m = n;
    this->values = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    if (eye) {
        for (size_t i = 0; i < n; i++) {
            this->values[i][i] = 1.0;
        }
    }
}

Matrix::Matrix(size_t n, size_t m) {
    this->n = n;
    this->m = m;
    this->values = std::vector<std::vector<double>>(n, std::vector<double>(m, 0.0));
}

Matrix::Matrix(const Matrix& other) : values(other.values) {
    this->n = other.n;
    this->m = other.m;
}

Matrix::Matrix(Matrix&& other) : values(std::move(other.values)) {
    this->n = other.n;
    this->m = other.m;
}

Matrix::Matrix(std::string& file_name) {
    std::ifstream infile(file_name);
    size_t n, m;

    infile >> n >> m;
    this->n = n;
    this->m = m;
    this->values = std::vector<std::vector<double>>(n, std::vector<double>(m, 0.0));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            infile >> this->values[i][j];
        }
    }

    infile.close();
}

Matrix& Matrix::operator=(const Matrix& other) {
    this->n = other.n;
    this->m = other.m;
    this->values = other.values;

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (this->n != other.n || this->m != other.m) {
        throw std::runtime_error("Matrices should have the same size");
    }

    for (size_t i = 0; i < this->n; i++) {
        for (size_t j = 0; j < this->m; j++) {
            this->values[i][j] += other.values[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (this->n != other.n || this->m != other.m) {
        throw std::runtime_error("Matrices should have the same size");
    }

    for (size_t i = 0; i < this->n; i++) {
        for (size_t j = 0; j < this->m; j++) {
            this->values[i][j] -= other.values[i][j];
        }
    }

    return *this;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.m != rhs.n) {
        throw std::runtime_error("Matrix sizes should be coresponding");
    }
    
    Matrix result(lhs.n, rhs.m);

    for (size_t i = 0; i < lhs.n; i++) {
        for (size_t j = 0; j < rhs.m; j++) {
            double itm = 0;

            for (size_t k = 0; k < lhs.m; k++) {
                itm += lhs.values[i][k] * rhs.values[k][j];
            }

            result.values[i][j] = itm;
        }
    }

    return result;
}

Matrix& Matrix::operator*=(const double other) {
    for (size_t i = 0; i < this->n; i++) {
        for (size_t j = 0; j < this->m; j++) {
            this->values[i][j] *= other;
        }
    }

    return *this;
}

Matrix& Matrix::operator/=(const double other) {
    for (size_t i = 0; i < this->n; i++) {
        for (size_t j = 0; j < this->m; j++) {
            this->values[i][j] /= other;
        }
    }

    return *this;
}

Matrix Matrix::operator^(int n) {
    if (this->n != this->m) {
        std::cout << this->n << ' ' << this->m << std::endl;
        throw std::runtime_error("Matrix sizes should be equal");
    }
	Matrix res(this->n, true);
    Matrix tmp(*this);

	while (n) {
        if (n & 1)
			res = res * tmp;
		tmp = tmp * tmp;
		n >>= 1;
    }

    return res;
}

std::vector<double> Matrix::operator*=(const std::vector<double> other) {
    if (this->m != other.size()) {
        throw std::invalid_argument("matrix size does not match");
    }

    std::vector<double> result(this->m, 0.0);

    for (size_t i = 0; i < this->n; i++) {
        for (size_t j = 0; j < this->m; j++) {
            result[j] += this->values[i][j] * other[j];
        }
    }

    return result;
}

std::pair<size_t, size_t> Matrix::size() const {
    return {this->n, this->m};
}

std::istream& operator>>(std::istream& inp, Matrix& matrix) {
    for (size_t i = 0; i < matrix.size().first; i++) {
        for (size_t j = 0; j < matrix.size().second; j++) {
            inp >> matrix[i][j];
        }
    }

    return inp;
}

void Matrix::to_file(std::string& file_name) {
    std::ofstream outfile(file_name);

    outfile << this->n << ' ' << this-> m << std::endl;

    for (size_t i = 0; i < this->n; i++) {
        for (size_t j = 0; j < this->m; j++) {
            outfile << this->values[i][j] << ' ';
        }
        outfile << std::endl;
    }

    outfile.close();
}
