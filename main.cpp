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
 * Convert a string to lowercase in place.
 *
 * @param orig The string to modify.
 */
void lowercase(std::string& orig)
{
    for (size_t i = 0; i < orig.length(); ++i) {
        orig[i] = std::tolower(orig[i]);
    }
}


/**
 * Parse the stream into individual tokens and keep count of the number
 * of times each token occurs in the document.
 *
 * @param fs The text stream to be parsed.
 * @return A map of tokens and their associated counts for this document.
 */
std::unordered_map<std::string, unsigned int> tokenize(const std::string& line, size_t ngram_size, bool casefold)
{
    std::unordered_map<std::string, unsigned int> token_counts;
    std::string token;

    // Walk through the string and extract fixed length tokens
    // consisting of adjacent characters, until the end of the string is reached.
    // For the string "hello world" and ngram_size=2, the tokens would be:
    //  "he", "el", "ll", "lo", "o ", " w", "wo", "or", "rl", "ld"
    size_t pos = 0;
    while (pos < line.length())
    {
        // Grab a token consisting of `ngram_size` adjacent characters,
        token = line.substr(pos++, ngram_size);

        // Case-insensitive tokenization: convert to lowercase
        if (casefold) {
            lowercase(token);
        }
        // If the token exists, increment its count.
        // Otherwise, set initial count to 1.
        if (token_counts.find(token) != token_counts.end()) {
            token_counts[token] += 1;
        } else {
            token_counts[token] = 1;
        }
    }
    return token_counts;
}


/**
 * Get a set of unique keys from a vector of unordered_maps.
 * @param maps A vector of unordered_maps.
 * @return A set of all unique keys across the maps.
 */
std::set<std::string> uniqueKeys(const std::vector<std::unordered_map<std::string, unsigned int>>& maps)
{
    std::set<std::string> unique;
    for (const auto& map: maps) {
        for (const auto& kv: map) {
            unique.insert(kv.first);
        }
    }
    return unique;
}


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


int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: LexicalTextSimilarity datafile count" << std::endl;
        return 1;
    }

    std::string data_file_path = argv[1];
    char *p_end{};
    unsigned int count = std::strtoul(argv[2], &p_end, 10);

    using FrequencyMap = std::unordered_map<std::string, unsigned int>;

    const int ngram_size = 2;

    // Get the token counts for each document
    std::vector<FrequencyMap> doc_freq_maps;
    std::ifstream fs(data_file_path);
    std::string line;
    int i = 0;
    while (std::getline(fs, line) && i++ < count) {
        doc_freq_maps.push_back(tokenize(line, ngram_size, true));
    }

    // Construct the set of unique tokens across all documents
    // This set will define the vector space used for constructing
    // the term frequency matrix.
    std::set<std::string> unique_tokens = uniqueKeys(doc_freq_maps);

    // Embed the document frequencies into the term vector space
    std::vector<std::vector<float>> embedded_frequencies;
    for (const auto& doc_token_map: doc_freq_maps)
    {
        std::vector<float> embedded = embed(doc_token_map, unique_tokens);
        normalize(embedded);
        embedded_frequencies.emplace_back(embedded);
    }

    auto mt = getTranspose(embedded_frequencies);
    auto result = matrixMultiply(embedded_frequencies, mt);
    printMatrix(result);

    return 0;
}
