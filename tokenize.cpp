#include <fstream>

#include "tokenize.h"


/**
 * Convert a string to lowercase in-place.
 *
 * @param orig The string to modify.
 */
static void lowercase(std::string& orig)
{
    for (size_t i = 0; i < orig.length(); ++i) {
        orig[i] = std::tolower(orig[i]);
    }
}


/**
 * Parse the string into individual tokens and keep count of the number
 * of times each token occurs.
 *
 * The resulting tokens are overlapping, fixed-length ngrams of adjacent characters.
 * For the string "hello world" and ngram_size=2, the tokens would be:
 *      "he", "el", "ll", "lo", "o ", " w", "wo", "or", "rl", "ld"
 *
 * @param line The string to be parsed.
 * @param ngram_len The length of each token.
 * @param ignorecase If true, ignore case sensitivity.
 * @return A map of tokens and their associated counts for this document.
 */
std::unordered_map<std::string, unsigned int>
        tokenize(const std::string& line, size_t ngram_len, bool ignorecase)
{
    std::unordered_map<std::string, unsigned int> token_counts;
    std::string token;

    // Walk through the string and extract fixed length tokens
    // consisting of adjacent characters, until the end of the string is reached.
    size_t pos = 0;
    while (pos < line.length())
    {
        // Grab a token consisting of `ngram_len` adjacent characters,
        token = line.substr(pos++, ngram_len);

        // Case-insensitive tokenization: convert to lowercase
        if (ignorecase) {
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
 * Perform tokenization on all text records in the given file.
 *
 * @param path The path of the file to read.
 * @param ngram_len The length of ngram tokens that will be produced.
 * @param max_count The maximum number of records to process.
 * @param ignorecase If true, ignore case sensitivity.
 * @return A vector with a map of tokens and their counts for each document.
 */
std::vector<std::unordered_map<std::string, unsigned int>>
        tokenizeFile(const std::string& path, unsigned short ngram_len, unsigned int max_count, bool ignorecase)
{
    std::vector<std::unordered_map<std::string, unsigned int>> doc_freq_maps;
    std::ifstream fs(path);
    std::string line;
    int i = 0;
    while (std::getline(fs, line) && i++ < max_count) {
        doc_freq_maps.push_back(tokenize(line, ngram_len, ignorecase));
    }
    return doc_freq_maps;
}

