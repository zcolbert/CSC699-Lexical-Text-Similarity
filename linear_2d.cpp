/******************************************************************************
 * Filename: linear.cpp
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Implementation of linear algebra operations on vectors and
 *              matrices.
 *****************************************************************************/

#include <cmath>    // sqrt
#include <iostream>
#include <vector>
#include <iomanip>

#include "linear_2d.h"

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


/**
 * Compute the magnitude of a vector.
 *
 * @param elements A vector of floating point values.
 * @return The magnitude of the given vector.
 */
float magnitude(const std::vector<float>& elements)
{
    float sum = 0.0f;
    for (const float& elem: elements) {
        sum += elem * elem;
    }
    return std::sqrt(sum);
}


/**
 * Normalize a vector in place.
 *
 * @param elements The vector to normalize.
 */
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

/**
 * Normalize all rows of a matrix in place.
 *
 * @param elements The matrix to normalize.
 */
void normalizeMatrix(std::vector<std::vector<float>>& elements)
{
    for (auto& row: elements) {
        normalize(row);
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

/**
 * Embed the frequency map's values onto the vector space of the given vocabulary.
 *
 * @param freq_map A map of terms and their frequencies.
 * @param basis A unique set of all terms in the vocabulary.
 * @return A vector of term frequencies embedded into the basis vector space.
 */
std::vector<float> getEmbeddedVector(
        const std::unordered_map<std::string, unsigned int>& freq_map,
        const std::set<std::string>& vocabulary)
{
    std::vector<float> embedded;
    embedded.reserve(vocabulary.size());

    for (const auto& token: vocabulary)
    {
        unsigned int freq = 0;
        if (freq_map.find(token) != freq_map.end()) {
            freq = freq_map.at(token);
        }
        embedded.push_back(static_cast<float>(freq));
    }
    return embedded;
}

std::vector<std::vector<float>> getTermFrequencyMatrix(
        const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
        const std::set<std::string>& vocabulary)
{
    std::vector<std::vector<float>> matrix;
    matrix.reserve(doc_freq_maps.size());

    for (const auto& doc: doc_freq_maps) {
        matrix.emplace_back(getEmbeddedVector(doc, vocabulary));
    }
    return matrix;
}