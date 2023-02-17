# ==============================================================================
# Program:  merge.py
# Author:   Zachary Colbert <zcolbert@sfsu.edu>
# Purpose:  Consolidate a set of text files into a single CSV.
#
# Description:
#   The parent directory data/aclImdb contains a set of text files within
#   the directory structure. This script locates each of those text files,
#   reads their contents, and writes them into a single CSV file along
#   with the file path from which the text was read. Each row in the CSV
#   file corresponds to a single text file from this directory tree.
# ==============================================================================

import csv
import pathlib


DATA_ROOT = '../aclImdb'  # directory containing all data files
OUTFILE_PATH = '../movie_reviews_combined.csv'


def main():
    data_root_path = pathlib.Path(DATA_ROOT).resolve()

    # Recursively find all .txt files in the directory tree
    # The desired files have a name format like: 123_1.txt
    text_file_paths = data_root_path.glob('**/[0-9]*_[0-9].txt')

    headers = ['Document ID', 'Source Document', 'Text']

    with open(OUTFILE_PATH, 'w') as outfile:
        writer = csv.writer(outfile)
        writer.writerow(headers)

        # Open each of the text files and write them into the CSV
        for i, path in enumerate(text_file_paths):
            with open(path, 'r') as infile:
                row = [
                    i + 1,                                    # assign a document ID
                    path.relative_to(data_root_path.parent),  # relative path of source file
                    infile.read()                             # text contents of file
                ]
                writer.writerow(row)


if __name__ == '__main__':
    main()
