/******************************************************************************
 * Filename: linear.cpp
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Implementation of linear algebra operations on vectors and
 *              matrices.
 *****************************************************************************/

#include "linearflat.h"

#include <cmath>    // sqrt


/**
 * Calculate the magnitude of a vector from [start, end)
 * as the square root of the sum of squares.
 *
 * @param elements The vector of numeric elements.
 * @param start The starting index of the vector.
 * @param end The ending index of the vector (non-inclusive).
 * @return The magnitude of the vector.
 */
float magnitude(const std::vector<float>& elements, size_t start, size_t end)
{
    float sum = 0.0f;
    for (size_t i = start; i < end; ++i) {
        sum += elements[i] * elements[i];
    }
    return std::sqrt(sum);
}

/**
 * Normalize a vector row in the given matrix existing at [start, end).
 *
 * @param matrix A row-wise matrix of vector elements.
 * @param start The starting index of this row.
 * @param end The ending index of this row, non-inclusive.
 */
void normalizeRow(std::vector<float>& matrix, size_t start, size_t end)
{
    float mag = magnitude(matrix, start, end);
    for (size_t i = start; i < end; ++i) {
        matrix[i] = matrix[i] / mag;
    }
}

/**
 * Normalize each row vector in the given matrix.
 * @param matrix The row-wise matrix of vector elements.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in each row.
 */
void normalizeMatrix(std::vector<float>& matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        size_t start = i * cols;
        size_t end = start + cols;
        normalizeRow(matrix, start, end);
    }
}

/**
 * Produce the transpose of the given matrix.
 *
 * @param matrix The original N x M matrix.
 * @param rows The number of rows in the matrix (N).
 * @param cols The number of columns per row (M).
 * @return The transpose of the matrix, with dimensions M x N.
 */
std::vector<float> transpose(const std::vector<float>& matrix, size_t rows, size_t cols)
{
    std::vector<float> m_T(rows * cols);

    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            m_T[c * rows + r] = matrix[r * cols + c];
        }
    }
    return m_T;
}

/**
 * Perform a matrix multiplication of lhs x rhs and return the resulting matrix.
 *
 * @param lhs The left-hand operand matrix, with dimensions N x M.
 * @param rhs The right-hand operand matrix, with dimensions M x N.
 * @param n The number of rows in the left matrix, columns in the right matrix.
 * @param m The number of columns in the left matrix, rows in the right matrix.
 * @return An N x N matrix containing the multiplication results.
 */
std::vector<float> matrixMultiply(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m)
{
    std::vector<float> result(n * n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                result[i * n + j] += lhs[i * m + k] * rhs[k * n + j];
            }
        }
    }
    return result;
}
