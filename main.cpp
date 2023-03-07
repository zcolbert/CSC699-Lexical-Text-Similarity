/******************************************************************************
 * Program: LexicalTextSimilarity
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Computes the lexical similarity between the text contents
 *              of a set of input documents.
 *****************************************************************************/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

#include "linear.h"
#include "tokenize.h"


/**
 * Get a set of unique keys from a vector of unordered_maps.
 * @param maps A vector of unordered_maps.
 * @return A set of all unique keys across the maps.
 */
std::set<std::string> extractUniqueKeys(const std::vector<std::unordered_map<std::string, unsigned int>>& maps)
{
    std::set<std::string> unique;
    for (const auto& map: maps) {
        for (const auto& kv: map) {
            unique.insert(kv.first);
        }
    }
    return unique;
}


/**
 * Embed the frequency map's values onto the vector space of the given basis.
 *
 * @param freq_map A map of terms and their frequencies.
 * @param basis A unique set of all terms in the vocabulary.
 * @return A vector of term frequencies embedded into the basis vector space.
 */
std::vector<float> embed(const std::unordered_map<std::string, unsigned int>& freq_map,
                         const std::set<std::string>& basis)
{
    std::vector<float> embedded(basis.size());

    for (const auto& elem: basis)
    {
        unsigned int freq = 0;
        if (freq_map.find(elem) != freq_map.end()) {
            freq = freq_map.at(elem);
        }
        embedded.push_back(static_cast<float>(freq));
    }
    return embedded;
}

void printRow(const std::vector<float>& matrix, size_t start, size_t end)
{
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << '<';
    for (size_t i = start; i < end - 1; ++i) {
        std::cout << std::right << std::setw(6) << matrix[i] << ", ";
    }
    std::cout << matrix[end-1] << " >" << std::endl;
}

void printMatrix(const std::vector<float>& matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; ++i)
    {
        size_t start = i * cols;
        size_t end = start + cols;
        printRow(matrix, start, end);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: LexicalTextSimilarity datafile count" << std::endl;
        return 1;
    }

    std::string data_file_path = argv[1];
    char *p_end{};
    unsigned int max_count = std::strtoul(argv[2], &p_end, 10);
    const short ngram_len = 2;

    // Get the token counts for each document
    auto doc_freq_maps = tokenizeFile(data_file_path, ngram_len, max_count, true);

    // Construct the set of unique tokens across all documents
    // This set will define the vector space used for constructing the term frequency matrix.
    std::set<std::string> unique_tokens = extractUniqueKeys(doc_freq_maps);

    // Embed the document frequencies into the term vector space
    // and produce a matrix from the normalized vectors
    size_t cols = unique_tokens.size();
    size_t rows = doc_freq_maps.size();

    std::vector<float> matrix(rows * cols, 0);

    int idx = 0;
    for (const auto& freq_map: doc_freq_maps)
    {
        for (const auto& tkn: unique_tokens)
        {
            if (freq_map.find(tkn) != freq_map.end()) {
                matrix[idx] = static_cast<float>(freq_map.at(tkn));
            }
            ++idx;
        }
    }
    normalizeMatrix(matrix, rows, cols);

    auto m_T = transpose(matrix, rows, cols);
    auto result = matrixMultiply(matrix, m_T, rows, cols);

    return 0;
}
