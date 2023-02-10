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
            if (token_counts.contains(token)) {
                token_counts[token] += 1;
            }
            else {
                token_counts[token] = 1;
            }
        }
    }
    else {
        throw std::runtime_error("Parse error: file stream is invalid");
    }
    return token_counts;
}


int main()
{
    std::ifstream fs("data/JekyllAndHide.txt");
    auto tokens = tokenize(fs);
    for (auto tkn: tokens) {
        std::cout << tkn.first << ": " << tkn.second << std::endl;
    }
    return 0;
}
