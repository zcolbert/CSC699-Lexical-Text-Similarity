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

#include "tokenize.h"
#include "LTS.h"


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

    execute(doc_freq_maps, unique_tokens);

    return 0;
}
