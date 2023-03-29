import csv

#parse the reports
# find the tables
# aggregate
# build the new tables

reports = ['ijk.csv', 'kij.csv']


def print_table(rows):
    for row in rows:
        print(row)
    print()


def main():
    tables = dict()

    table_name = ''
    group_name = ''
    title = ''
    rows = []

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

                    # If there is a table, flush it
                    if len(rows) > 0:
                        if title not in tables:
                            tables[title] = list()
                        tables[title].extend(rows)

                        # reset the table tracking data
                        table_name = ''
                        group_name = ''
                        title = ''
                        rows = []

                    # start a new table
                    table_name = row[1]
                    group_name = row[2]
                    # construct a title for this table, also used as a grouping key
                    title = f'{group_name} - {table_name}'

                    row = next(reader)  # discard the delimiting row 
                    # The next row is the table headers. Add field name to first column.
                    row.insert(0, 'Executable')  
                    rows.append(row)
                    continue

                # The report file contains sections that describe the system hardware.
                # These informational sections begin with a row containing the STRUCT 
                # keyword in the first column. Ignore any rows belonging to this section.
                elif row[0] == 'STRUCT':
                    # ignore any rows until the next table is encountered
                    reading = False

                    # If there is a table, flush it
                    if len(rows) > 0:
                        if title not in tables:
                            tables[title] = list()
                        tables[title].extend(rows)

                        # reset the table data
                        table_name = ''
                        group_name = ''
                        title = ''
                        rows = []
                
                # If the parser is currently consuming table rows, process the current row.
                if reading:
                    row.insert(0, exe)  # insert the executable into the first column
                    rows.append(row)
    
    # display the table
    for title, rows in tables.items():
        print(title)
        for row in rows:
            print(row)
        print()


if __name__ == '__main__':
    main()