/******************************************************************************
 * Program: LexicalTextSimilarity
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Computes the lexical similarity between the text contents
 *              of a set of input documents.
 *****************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

#include "linear.h"


/**
 * Parse the stream into individual tokens and keep count of the number
 * of times each token occurs in the document.
 *
 * @param fs The text stream to be parsed.
 * @return A map of tokens and their associated counts for this document.
 */
std::unordered_map<std::string, unsigned int> tokenize(std::ifstream& fs)
{
    std::unordered_map<std::string, unsigned int> token_counts;
    std::string token;

    if (fs.is_open()) {
        while (fs) {
            fs >> token;
            // If the token exists, increment its count. Otherwise, set initial count to 1.
            token_counts.contains(token) ? token_counts[token] += 1 : token_counts[token] = 1;
        }
    }
    else {
        throw std::runtime_error("Parse error: file stream is invalid");
    }
    return token_counts;
}


int main()
{
    using FrequencyMap = std::unordered_map<std::string, unsigned int>;

    std::set<std::string> unique_tokens;
    std::vector<FrequencyMap> doc_freq_maps;

    std::vector<std::string> document_paths = {
            //"data/MobyDick.txt",
            //"data/Frankenstein.txt"
            "data/loremipsum_5p.txt",
            "data/loremipsum_10p.txt"
    };

    // Get the token counts for each document
    for (const auto& path: document_paths) {
        std::ifstream fs(path);
        doc_freq_maps.push_back(tokenize(fs));
    }

    // Construct the set of unique tokens across all documents
    // This set will define the vector space used for constructing
    // the term frequency matrix.
    for (const auto& doc_token_map: doc_freq_maps) {
        for (const auto& token_count: doc_token_map) {
            unique_tokens.insert(token_count.first);
        }
    }

    // Project the document frequencies onto the term vector space
    std::vector<std::vector<float>> projected_frequencies;
    projected_frequencies.reserve(document_paths.size());

    for (const auto& doc_token_map: doc_freq_maps)
    {
        std::vector<float> projected_term_freq;

        for (const auto& token: unique_tokens)
        {
            unsigned int count = 0;
            if (doc_token_map.contains(token)) {
                count = doc_token_map.at(token);
            }
            projected_term_freq.push_back(static_cast<float>(count));
        }
        normalize(projected_term_freq);
        projected_frequencies.emplace_back(projected_term_freq);
    }

    auto mt = getTranspose(projected_frequencies);
    auto result = matrixMultiply(projected_frequencies, mt);
    printMatrix(result);

    return 0;
}
