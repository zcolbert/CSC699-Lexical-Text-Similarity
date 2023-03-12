#include "LTS.h"

#include <cmath>  // sqrt
#include <iomanip>
#include <iostream>

std::vector<std::vector<float>> matrixMultiply(const std::vector<std::vector<float>>& lhs,
                                               const std::vector<std::vector<float>>& rhs);

float magnitude(const std::vector<float>& elements);
void normalize(std::vector<std::vector<float>>& elements);
std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>>& matrix);
void printVector(const std::vector<float>& vec);
void printMatrix(const std::vector<std::vector<float>>& matrix);

/**
 * Perform matrix multiplication and return a result matrix.
 *
 * @param lhs The left-side operand matrix (N x M)
 * @param rhs The right-side operand matrix (M x N)
 * @return An N x N matrix containing the multiplication result.
 */
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
    for (const auto& elem: elements) {
        sum += elem * elem;
    }
    return std::sqrt(sum);
}


/**
 * Normalize a vector in place.
 *
 * @param elements The vector to normalize.
 */
void normalize(std::vector<std::vector<float>>& elements)
{
    for (auto& row: elements)
    {
        float denom = magnitude(row);

        if (denom == 0) {
            throw std::runtime_error("Cannot normalize zero vector");
        }
        // Divide each element by the vector's magnitude
        for (float &elem: row) {
            elem = elem / denom;
        }
    }
}

/**
 * Compute the transpose of the given matrix.
 *
 * @param matrix A matrix of floating point values.
 * @return The transpose of the input matrix.
 */
std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>>& matrix)
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


/**
 * Compute the dot (scalar) product of the given vectors.
 *
 * @param lhs The left-hand operand vector.
 * @param rhs The right-hand operand vector.
 * @return The scalar product of the two given vectors.
 */
float dot(const std::vector<float>& lhs, const std::vector<float>& rhs)
{
    float result = 0;
    for (int i = 0; i < lhs.size(); i++) {
        result += lhs[i] * rhs[i];
    }
    return result;
}


/**
 * Display a formatted output of the given vector.
 *
 * @param vec The vector to print.
 */
void printVector(const std::vector<float>& vec)
{
    std::cout << "<";
    for (int i = 0; i < vec.size() - 1; ++i) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size()-1] << ">" << std::endl;
}


/**
 * Display a formatted output of the given matrix.
 *
 * @param matrix The matrix to print.
 */
void printMatrix(const std::vector<std::vector<float>>& matrix)
{
    std::cout << std::fixed;
    std::cout << std::setprecision(5);
    for (auto v: matrix) {
        printVector(v);
    }
}

void execute(const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
             const std::set<std::string>& unique_tokens)
{
    const size_t rows = doc_freq_maps.size();
    const size_t cols = unique_tokens.size();

    std::vector<std::vector<float>> matrix;
    matrix.reserve(rows);

    for (size_t i = 0; i < doc_freq_maps.size(); ++i)
    {
        std::vector<float> frequencies(cols, 0);
        std::cout << frequencies.size() << std::endl;
        const auto &doc_map = doc_freq_maps[i];

        size_t idx = 0;
        for (const auto &token: unique_tokens) {
            if (doc_map.find(token) != doc_map.end()) {
                frequencies[idx] = static_cast<float>(doc_map.at(token));
            }
            ++idx;
        }
        matrix.push_back(frequencies);
    }
    normalize(matrix);
    auto m_T = transpose(matrix);
    auto result = matrixMultiply(matrix, m_T);
}