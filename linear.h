#pragma once

#include <cmath>
#include <iostream>
#include <vector>


std::vector<std::vector<float>> matrixMultiply(const std::vector<std::vector<float>>& lhs,
                                               const std::vector<std::vector<float>>& rhs);

float magnitude(const std::vector<float>& elements);
void normalize(std::vector<float>& elements);
std::vector<std::vector<float>> getTranspose(const std::vector<std::vector<float>>& matrix);
void printVector(const std::vector<float>& vec);
void printMatrix(const std::vector<std::vector<float>> matrix);
float dot(const std::vector<float>& lhs, const std::vector<float>& rhs);
