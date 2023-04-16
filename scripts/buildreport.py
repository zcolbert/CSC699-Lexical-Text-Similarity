import argparse
import csv
import os

import likwidcsv



def load_report_names_from_file(filename):
    with open(filename, 'r') as infile:
        return [line.strip() for line in infile]
    

def write_combined_file(filepath, tables):
    with open(filepath, 'w') as outfile:
        writer = csv.writer(outfile)
        # Write a report title and a few blank lines
        writer.writerow(['Combined reports'])
        writer.writerow([])
        writer.writerow([])

        # Write each table's group and name, followed by its header and all of its rows
        for table in tables.values():
            writer.writerow([table.group, table.name])
            writer.writerow(table.headers)
            for row in table.rows:
                writer.writerow(row)
            writer.writerow([])


def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('filename')
    parser.add_argument('-o', '--output')

    return parser.parse_args()


def main():
    args = parse_args()

    reports = load_report_names_from_file(args.filename)
    tables = likwidcsv.parse_reports(reports)

    # Write the aggregated reports to an output file
    outpath = 'combined.csv'
    if args.output:
        outpath = args.output

    write_combined_file(outpath, tables)



if __name__ == '__main__':
    main()
