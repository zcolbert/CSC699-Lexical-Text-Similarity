/******************************************************************************
 * Filename: tokenize.h
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description:
 *      Interface for string tokenization functions.
 *****************************************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>


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
        tokenize(const std::string& line, size_t ngram_len, bool ignorecase);


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
        tokenizeFile(const std::string& path, unsigned short ngram_len, unsigned int max_count, bool ignorecase);

