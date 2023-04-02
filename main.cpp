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
#include <getopt.h>
#include <string>
#include <set>

#include "linear.h"
#include "tokenize.h"


int main(int argc, char* argv[])
{
    // Initialize feature flags
    bool print_result = false;
    bool use_bco = false;

    // Initialize operational parameters
    std::string datafile;
    size_t data_count = 0;
    size_t blocksize = 0;
    const short ngram_len = 2;

    // Create a function pointer for a specific permutation of the matrix multiply operation
    // This algorithm is used as a default, or can be chosen based on a command line argument like: "--mmloop ijk"
    void (*mmfunc_ptr)(const std::vector<float>&, const std::vector<float>&, std::vector<float>&, size_t, size_t) = &matrixMultiply_ijk;

    // Construct the array of possible arguments.
    // If .flag is NULL, getopt_long returns .val (otherwise .val would set a variable)
    static struct option long_options[] = {
            {"mmloop", required_argument, NULL, 0 },
            {"bco", required_argument, NULL, 0 },
            {"data", required_argument, NULL, 0 },
            {"count", required_argument, NULL, 0 },
            {"print", no_argument, NULL, 0 }
    };

    // Parse the command line arguments
    std::string opt_name;
    std::string opt_val;
    // shortopts would be handled by switching on the value of c
    // Otherwise, evaluation of longopts sets c to 0
    // If there are no shortopts, then this switch is unnecessary. Read until c == -1
    int opt_idx = 0;
    while (getopt_long(argc, argv, "", long_options, &opt_idx) >= 0)
    {
        // Store the char* values in a std::string for convenience
        opt_name = long_options[opt_idx].name;
        if (optarg) { opt_val = optarg; }

        // Select the function for the indicated matrix multiplication loop permutation
        if (opt_name == "mmloop")
        {
            if (opt_val == "ijk") {
                mmfunc_ptr = &matrixMultiply_ijk;
            } else if (opt_val == "ikj") {
                mmfunc_ptr = &matrixMultiply_ikj;
            } else if (opt_val == "jki") {
                mmfunc_ptr = &matrixMultiply_jki;
            } else if (opt_val == "jik") {
                mmfunc_ptr = &matrixMultiply_jik;
            } else if (opt_val == "kji") {
                mmfunc_ptr = &matrixMultiply_kji;
            } else if (opt_val == "kij") {
                mmfunc_ptr = &matrixMultiply_kij;
            }
        }
        // Enable block copy optimization and set the block size
        else if (opt_name == "bco") {
            use_bco = true;
            blocksize = stoull(opt_val);
        }
        // Set the input data file path
        else if (opt_name == "data") {
            datafile = opt_val;
        }
        // Set the number of records to process from the input data
        else if (opt_name == "count") {
            data_count = stoull(opt_val);
        }
        // Print the result matrix
        else if (opt_name == "print") {
            print_result = true;
        }
    }

    // Verify that a data file was supplied
    if (datafile.empty()) {
        std::cout << "Missing data file. Aborting." << std::endl;
        exit(1);
    }
    if (data_count <= 0) {
        std::cout << "Data count unspecified. Reading all records in the supplied file." << std::endl;
    }

    // Get the token counts for each document
    auto doc_freq_maps = tokenizeFile(datafile, ngram_len, data_count, true);

    // Construct the set of unique tokens across all documents
    // This set will define the vector space used for constructing the term frequency matrix.
    std::set<std::string> unique_tokens = extractUniqueKeys(doc_freq_maps);

    const size_t rows = doc_freq_maps.size();
    const size_t cols = unique_tokens.size();

    auto matrix = getTermFrequencyMatrix(doc_freq_maps, unique_tokens, rows, cols);
    normalizeMatrix(matrix, rows,cols);
    auto m_T = transpose(matrix, rows, cols);

    std::vector<float> result(rows * rows, 0);

    // Execute the selected algorithm
    if (mmfunc_ptr != nullptr)
    {
        if (use_bco) {
            matrixMultiply_bco(mmfunc_ptr, matrix, m_T, result, rows, cols, blocksize);
        } else {
            mmfunc_ptr(matrix, m_T, result, rows, cols);
        }
    }
    if (print_result) {
        std::cout << "Result matrix: " << std::endl;
        printMatrix(result, rows, rows);
    }

    return 0;
}
