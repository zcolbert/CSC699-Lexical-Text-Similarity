#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>


std::vector<std::vector<float>> matrixMultiply(const std::vector<std::vector<float>>& lhs,
                                               const std::vector<std::vector<float>>& rhs)
{
    size_t N = lhs.size();      // number of rows in the left operand
    size_t M = lhs[0].size();   // dimension of the vector space (number of columns)

    std::vector<std::vector<float>> result(N, std::vector<float>(N, 0));

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; ++j) {
            result[i][j] = 0;
            for (int d = 0; d < M; ++d) {
                result[i][j] += lhs[i][d] * rhs[d][j];
            }
        }
    }

    return result;
}


float magnitude(const std::vector<float>& elements)
{
    float sum = 0.0f;
    for (const float& elem: elements) {
        sum += elem * elem;
    }
    return std::sqrt(sum);
}

void normalize(std::vector<float>& elements)
{
    float denom = magnitude(elements);

    if (denom == 0) {
        throw std::runtime_error("Cannot normalize zero vector");
    }
    // Divide each element by the vector's magnitude
    for (float &elem: elements) {
        elem = elem / denom;
    }
}


std::vector<std::vector<float>> getTranspose(const std::vector<std::vector<float>>& matrix)
{
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    std::vector<std::vector<float>> matrix_transpose(
            cols,                                        // rows in transpose = cols in matrix
            std::vector<float>(rows, 0));  // cols in transpose = rows in matrix

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            matrix_transpose[col][row] = matrix[row][col];
        }
    }

    return matrix_transpose;
}

void printVector(const std::vector<float>& vec)
{
    std::cout << "<";
    for (int i = 0; i < vec.size() - 1; ++i) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size()-1] << ">" << std::endl;
}

void printMatrix(const std::vector<std::vector<float>> matrix)
{
    std::cout << std::fixed;
    std::cout << std::setprecision(5);
    for (auto v: matrix) {
        printVector(v);
    }
}

float dot(const std::vector<float>& lhs, const std::vector<float>& rhs)
{
    float result = 0;
    for (int i = 0; i < lhs.size(); i++) {
        result += lhs[i] * rhs[i];
    }
    return result;
}