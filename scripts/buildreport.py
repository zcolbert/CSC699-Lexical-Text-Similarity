import csv

#parse the reports
# find the tables
# aggregate
# build the new tables

reports = ['ijk.csv', 'kij.csv']


class Table:
    def __init__(self, group, name):
        self.group = group
        self.name = name
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


def main():
    tables = dict()
    table = None

    for report in reports:
        exe = report
        with open(report, 'r') as infile:
            reader = csv.reader(infile)

            for row in reader:

                # Each valid table begins with a delimiting row which has 
                # the word TABLE in the first column. When this is encountered,
                # process the existing table (if any) and start consuming rows for 
                # this new table.
                if row[0] == 'TABLE':
                    # start consuming rows
                    reading = True

                    # If this section marks the end of the previous table, flush it.
                    if table:
                        if table.title in tables:
                            tables[table.title].add_rows(table.rows)
                        else:
                            tables[table.title] = table

                        table = None

                    # start a new table
                    table = Table(group=row[2], name=row[1])

                    row = next(reader)  # discard the delimiting row 
                    # The next row is the table headers. Add field name to first column.
                    row.insert(0, 'Executable')  
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
                    row.insert(0, exe)  # insert the executable into the first column
                    #rows.append(row)
                    if table:
                        table.add_row(row)
    

    for title, table in tables.items():
        print(table)
        print(title)
        print(table.headers)
        for row in table.rows:
            print(row)
        print()


if __name__ == '__main__':
    main()