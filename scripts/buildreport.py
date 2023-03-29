import csv

#parse the reports
# find the tables
# aggregate
# build the new tables

report = 'ijk.csv'


def print_table(rows):
    for row in rows:
        print(row)
    print()


def main():
    table_name = ''
    group_name = ''
    title = ''
    rows = []
    exe = 'LTS #1'

    with open(report, 'r') as infile:
        reader = csv.reader(infile)

        for row in reader:

            if row[0] == 'TABLE':
                # start consuming rows
                reading = True
                # If there is a table, flush it
                if len(rows) > 0:
                    print(title)
                    print_table(rows)
                    rows = []

                # start a new table
                table_name = row[1]
                group_name = row[2]
                # construct a title for this table, also used as a grouping key
                title = f'{group_name} - {table_name}'

                # consume the delimiting row and fetch the table header in the next row
                row = next(reader)
                # add the field name into the first column and process the header row
                row.insert(0, 'Executable')  
                rows.append(row)
                continue


            elif row[0] == 'STRUCT':
                # ignore any rows until the next table is encountered
                reading = False
                # If there is a table, flush it
                if len(rows) > 0:
                    print(title)
                    print_table(rows)
                    rows = []
            
            if reading:
                row.insert(0, exe)  # insert the executable into the first column
                rows.append(row)


if __name__ == '__main__':
    main()