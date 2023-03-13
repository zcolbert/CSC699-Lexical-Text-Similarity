/******************************************************************************
 * Filename: linear.h
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Interface of linear algebra operations on vectors and
 *              matrices.
 *****************************************************************************/

#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>


std::vector<std::vector<float>> matrixMultiply(const std::vector<std::vector<float>>& lhs,
                                               const std::vector<std::vector<float>>& rhs);

float magnitude(const std::vector<float>& elements);
void normalize(std::vector<float>& elements);
void normalizeMatrix(std::vector<std::vector<float>>& elements);
std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>>& matrix);
void printVector(const std::vector<float>& vec);
void printMatrix(const std::vector<std::vector<float>>& matrix);
float dot(const std::vector<float>& lhs, const std::vector<float>& rhs);

/**
 * Embed the frequency map's values onto the vector space of the given vocabulary.
 *
 * @param freq_map A map of terms and their frequencies.
 * @param basis A unique set of all terms in the vocabulary.
 * @return A vector of term frequencies embedded into the basis vector space.
 */
std::vector<float> getEmbeddedVector(
        const std::unordered_map<std::string, unsigned int>& freq_map,
        const std::set<std::string>& vocabulary);

std::vector<std::vector<float>> getTermFrequencyMatrix(
        const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
        const std::set<std::string>& vocabulary);
