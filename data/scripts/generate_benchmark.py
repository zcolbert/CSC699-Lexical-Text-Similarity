# ==============================================================================
# Program:  generate_benchmark.py
# Author:   Zachary Colbert <zcolbert@sfsu.edu>
# Purpose:  Produce a benchmark similarity score for a test data set.
#
# Description:
#   Using a known implementation of the cosine text similarity algorithm,
#   produce a document containing similarity scores for a test data set.
#   This score data can be used as a benchmark to gauge the accuracy of
#   other implementations of the same algorithm.
#
#   This script uses the scikit-learn implementation of cosine similarity.
# ==============================================================================

import csv
from typing import List

import pandas as pd
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity


DATAPATH = '../movie_reviews_combined.csv'


def load_documents(path: str, column_idx: int, row_count: int = None, skip_headers: bool = False) -> List[str]:
    """Load a list of text samples from a CSV file.

    :param path: The path of the CSV file containing the text samples.
    :param column_idx: The numeric index of the column containing the text samples.
    :param row_count: A maximum number of records to read. Returns all records if count is None.
    :param skip_headers: Assume the first row contains headers: Skip the first row
        and do not include it in the text list or the row count.
    """
    documents = []

    with open(path, 'r') as infile:
        reader = csv.reader(infile)

        if skip_headers:
            next(reader)
        else:
            if row_count: row_count += 1  # increase row count to include header

        if row_count:  # return only `row_count` number of rows
            for i, row in enumerate(reader):
                if i >= row_count: break
                documents.append(row[column_idx])
        else:      # return all rows
            documents = [row[column_idx] for row in reader]

    return documents


def main():

    text_col_idx = 2
    row_count = 10000
    output_path = '../benchmark_' + str(row_count) + '.csv'

    documents = load_documents(DATAPATH,
                               column_idx=text_col_idx,
                               row_count=row_count,
                               skip_headers=True)

    count_vectorizer = CountVectorizer()
    sparse_matrix = count_vectorizer.fit_transform(documents)

    doc_term_matrix = sparse_matrix.todense()

    frame = pd.DataFrame(doc_term_matrix,
                         columns=count_vectorizer.get_feature_names_out(),
                         index=documents)

    scores = pd.DataFrame(cosine_similarity(frame, frame))
    scores.to_csv(output_path)


if __name__ == '__main__':
    main()
