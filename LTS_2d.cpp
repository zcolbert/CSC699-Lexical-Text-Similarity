#include "LTS.h"
#include "linear_2d.h"


void execute(const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
             const std::set<std::string>& vocabulary)
{
    auto matrix = getTermFrequencyMatrix(doc_freq_maps, vocabulary);
    normalizeMatrix(matrix);
    auto m_T = transpose(matrix);
    auto result = matrixMultiply(matrix, m_T);
}