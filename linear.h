/******************************************************************************
 * Filename: linear.h
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Interface of linear algebra operations on vectors and
 *              matrices.
 *****************************************************************************/
#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <string>


/**
 * Calculate the magnitude of a vector from [start, end)
 * as the square root of the sum of squares.
 *
 * @param elements The vector of numeric elements.
 * @param start The starting index of the vector.
 * @param end The ending index of the vector (non-inclusive).
 * @return The magnitude of the vector.
 */
float magnitude(const std::vector<float>& elements, size_t start, size_t end);

/**
 * Normalize a vector row in the given matrix existing at [start, end).
 *
 * @param matrix A row-wise matrix of vector elements.
 * @param start The starting index of this row.
 * @param end The ending index of this row, non-inclusive.
 */
void normalizeRow(std::vector<float>& matrix, size_t start, size_t end);

/**
 * Normalize each row vector in the given matrix.
 * @param matrix The row-wise matrix of vector elements.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in each row.
 */
void normalizeMatrix(std::vector<float>& matrix, size_t rows, size_t cols);

/**
 * Produce the transpose of the given matrix.
 *
 * @param matrix The original N x M matrix.
 * @param rows The number of rows in the matrix (N).
 * @param cols The number of columns per row (M).
 * @return The transpose of the matrix, with dimensions M x N.
 */
std::vector<float> transpose(const std::vector<float>& matrix, size_t rows, size_t cols);

/**
 * Perform a matrix multiplication of lhs x rhs and return the resulting matrix.
 *
 * @param lhs The left-hand operand matrix, with dimensions N x M.
 * @param rhs The right-hand operand matrix, with dimensions M x N.
 * @param n The number of rows in the left matrix, columns in the right matrix.
 * @param m The number of columns in the left matrix, rows in the right matrix.
 * @return An N x N matrix containing the multiplication results.
 */
std::vector<float> matrixMultiply(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);
std::vector<float> matrixMultiply_ijk(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);
std::vector<float> matrixMultiply_ikj(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);
std::vector<float> matrixMultiply_jik(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);
std::vector<float> matrixMultiply_jki(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);
std::vector<float> matrixMultiply_kij(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);
std::vector<float> matrixMultiply_kji(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m);

/* Matrix multiplication that populates the result matrix as an in/out parameter instead of a return value.
 * This is necessary to support the block/copy optimization which writes partial sections of the result in
 * separate steps.
 */
void matrixMultiply(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);
void matrixMultiply_ijk(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);
void matrixMultiply_ikj(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);
void matrixMultiply_jik(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);
void matrixMultiply_jki(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);
void matrixMultiply_kij(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);
void matrixMultiply_kji(const std::vector<float>& lhs, const std::vector<float>& rhs, std::vector<float>& result, size_t n, size_t m);

/* Matrix multiply with block-copy optimization */
void readBlock(std::vector<float>& dest, const std::vector<float>& src, size_t start_row, size_t start_col, size_t n, size_t blocksize);
void writeBlock(std::vector<float>& dest, const std::vector<float>& src, size_t start_row, size_t start_col, size_t n, size_t blocksize);

void matrixMultiply_bco(
        void(*mmfunc)(const std::vector<float>&, const std::vector<float>&, std::vector<float>&, size_t, size_t),
        const std::vector<float>& lhs,
        const std::vector<float>& rhs,
        std::vector<float>& result,
        size_t n, size_t m, size_t blocksize);

std::vector<float> getTermFrequencyMatrix(
        const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
        const std::set<std::string>& vocabulary,
        size_t rows, size_t cols);

void printRow(const std::vector<float>& matrix, size_t start, size_t end);
void printMatrix(const std::vector<float>& matrix, size_t rows, size_t cols);
