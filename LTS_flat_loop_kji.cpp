#include "LTS.h"
#include "linear.h"


std::vector<float> matrixMultiply_reordered(const std::vector<float>& lhs, const std::vector<float>& rhs, size_t n, size_t m)
{
    std::vector<float> result(n * n, 0);

    for (int k = 0; k < m; ++k) {
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                result[i * n + j] += lhs[i * m + k] * rhs[k * n + j];
            }
        }
    }
    return result;
}

void execute(const std::vector<std::unordered_map<std::string, unsigned int>>& doc_freq_maps,
             const std::set<std::string>& vocabulary)
{
    const size_t rows = doc_freq_maps.size();
    const size_t cols = vocabulary.size();

    auto matrix = getTermFrequencyMatrix(doc_freq_maps, vocabulary, rows, cols);
    normalizeMatrix(matrix, rows,cols);
    auto m_T = transpose(matrix, rows, cols);
    auto result = matrixMultiply_reordered(matrix, m_T, rows, cols);
    printMatrix(result, rows, rows);
}
