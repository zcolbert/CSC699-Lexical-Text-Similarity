import argparse
import csv
import os
import subprocess


def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('-e', '--exe', action='append', help='The executable to be run')
    parser.add_argument('-o', '--output', help='Specify the output directory')
    parser.add_argument('-f', '--force', action='store_true', help='Overwrite existing file')

    return parser.parse_args()


def main():

    args = parse_args()

    data_input_file = '../data/movie_reviews_combined.txt'
    data_record_count = '1000'

    plevels = [1, 2, 4]
    loop_permutations = ['ijk', 'ikj', 'jik', 'jki', 'kij', 'kji']
    block_sizes = [0, 16, 32, 64, 128, 256, 512, 1024, 2048]

    if args.exe is None or len(args.exe) == 0:
        print('Error: Must supply at least one executable')
        return


    rows = []

    for exe in args.exe:
        base_args = [f'./{exe}', '--data', data_input_file, '--count', data_record_count]

        for loop in loop_permutations:
            for size in block_sizes:
                for plevel in plevels:

                    print(f"Running '{exe}' with nthreads={plevel}, loop='{loop}', blocksize={size}", end=' ')

                    os.environ['OMP_NUM_THREADS'] = str(plevel)

                    args = []
                    args.extend(base_args)

                    args.extend(['--mmloop', loop])
                    if size > 0:
                        args.extend(['--bco', str(size)])

                    command = ' '.join(args)
                    p = subprocess.run(command, shell=True, capture_output=True)
                    runtime = float(p.stdout)
                    print(f'({runtime} s)')

                    rows.append([plevel, loop, size, runtime])

    headers = ['NThreads', 'Loop', 'Block Size', 'Runtime (s)']
    with open('runtimes.csv', 'w') as outfile:
        writer = csv.writer(outfile)

        writer.writerow(headers)
        writer.writerows(rows)

if __name__ == '__main__':
    main()
