#include "LTS.h"
#include "linear.h"


void execute(const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
             const std::set<std::string>& vocabulary)
{
    const size_t rows = doc_freq_maps.size();
    const size_t cols = vocabulary.size();

    auto matrix = getTermFrequencyMatrix(doc_freq_maps, vocabulary, rows, cols);
    normalizeMatrix(matrix, rows,cols);
    auto m_T = transpose(matrix, rows, cols);

    const size_t blocksize = 10;
    std::vector<float> result(rows * rows, 0);
    matrixMultiply_ijk_bco(matrix, m_T, result, rows, cols, blocksize);
}