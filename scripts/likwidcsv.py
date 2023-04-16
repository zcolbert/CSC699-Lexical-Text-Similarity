import csv
import os

from typing import Dict, Tuple


"""Represents a table of LIKWID perfctr data points for a single metric group"""
class Table:
    def __init__(self, name, group):
        self.name = name
        self.group = group
        self.rows = list()
        self.headers = list()

    def add_row(self, row):
        self.rows.append(row)

    def add_rows(self, rows):
        self.rows.extend(rows)

    @property
    def title(self):
        return f'{self.group} - {self.name}'

    def __eq__(self, rhs):
        return self.title == rhs.title

    def __hash__(self):
        return hash(self.title)

    def __repr__(self):
        return f"Table<group='{self.group}', name='{self.name}', rows={len(self.rows)}>"

    def print(self):
        print(self.title.upper())
        print(','.join(self.headers))
        for row in self.rows:
            print(','.join(row))


def parse_reports(report_paths):
    """Parse out the performance counter tables from a collection of
    CSV files and aggregate the data from each file into common tables.
    @param report_paths a list of paths to CSV files containing performance counter tables.
    @return A dict of performance counter tables with their titles as keys.
    """
    tables = dict()

    for report in report_paths:
        # Build an executable label from the name of the report
        exe = os.path.split(report)[-1].split('.csv')[0]
        # The executable name will uniquely identify each group of records in the tables
        report_tables = parse_likwid_csv(report, identifier=('Executable', exe))
        for title, table in report_tables.items():
            if title in tables:
                tables[title].add_rows(report_tables[title].rows)
            else:
                tables[title] = table

    return tables


def parse_likwid_csv(filepath, identifier : Tuple[str, str] = None) -> Dict[str, Table]:
    """Parse out all the performance counter tables in a single CSV file.
    @param filepath The path to a CSV file containing performance counter data.
    @param identifier A tuple containing a column title and value which uniquely identify this set of records.
    @return A dictionary of tables, with the titles of each table as the keys.
    """
    tables = dict()
    table = None
    reading = False

    with open(filepath, 'r') as infile:
        reader = csv.reader(infile)

        for row in reader:
            # Each valid table begins with a delimiting row which has
            # the word TABLE in the first column. When this is encountered,
            # process the existing table (if any) and start consuming rows for
            # this new table.

            if row[0] == 'TABLE':
                reading = True  # start consuming rows

                # If this section marks the end of the previous table, flush it.
                if table:
                    if table.title in tables:
                        tables[table.title].add_rows(table.rows)
                    else:
                        tables[table.title] = table

                    table = None

                # start a new table
                table = Table(name=row[1], group=row[2])

                row = next(reader)  # discard the delimiting row
                if identifier:
                    row.insert(0, identifier[0])
                table.headers = row
                continue

            # The report file contains sections that describe the system hardware.
            # These informational sections begin with a row containing the STRUCT
            # keyword in the first column. Ignore any rows belonging to this section.
            elif row[0] == 'STRUCT':
                # ignore any rows until the next table is encountered
                reading = False

                # If this section marks the end of the previous table, flush it.
                if table:
                    if table.title in tables:
                        tables[table.title].add_rows(table.rows)
                    else:
                        tables[table.title] = table

                    table = None

            # If the parser is currently consuming table rows, process the current row.
            if reading:
                if identifier:
                    row.insert(0, identifier[1])
                if table:
                    table.add_row(row)

    return tables


