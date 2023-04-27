#!/usr/bin/env python3

import argparse
import subprocess
from subprocess import PIPE, STDOUT
import os


exe_dir = '../build'

def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('executable', help='The executable to be run')
    parser.add_argument('-o', '--output', help='Specify the output directory')
    parser.add_argument('-g', '--group', help='Specify the likwid-perfctr group')
    parser.add_argument('-f', '--force', action='store_true', help='Overwrite existing file')

    return parser.parse_args()


def main():

    args = parse_args()
    print(args)

    if not args.group:
        print('Error: group not specified')
        return

    if args.output:
        out_dir = args.output
    else:
        out_dir = os.getcwd()

    print(f'Files will be output into {out_dir}')

    if not os.path.exists(out_dir):
        os.mkdir(out_dir)
        print(f'Created {out_dir}')

    likwid_tool = 'likwid-perfctr' 
    data_input_file = '../data/movie_reviews_combined.txt' 
    data_record_count = '1000'

    groups = [ args.group ]
    loop_permutations = ['ijk', 'ikj', 'jik', 'jki', 'kij', 'kji']
    block_sizes = [16, 32, 64, 128, 256, 512, 1024, 2048]
    #block_sizes = [16, 64, 1024, 2048]

    # Maintain a list of files generated during this process 
    # for easy retrieval in other scripts.
    output_files = []

    commands = []

    # Build commands for loop permutations
    for p in loop_permutations:
        cmd = [likwid_tool, '-f']
        for g in groups:
            cmd.extend(['-g', g])

        csvpath = f'{out_dir}/{p}.csv'

        if args.force or not os.path.exists(csvpath):
            output_files.append(csvpath)
            cmd.extend(['-o', csvpath])

            cmd.append(args.executable)
            cmd.extend(['--data', data_input_file])
            cmd.extend(['--count', data_record_count])
            cmd.extend(['--mmloop', p])
            commands.append(cmd)
        else:
            print(f'Skipping {csvpath} (already exists). Use -f (--force) to force overwrite.')

    # Run all loop permutations with block-copy optimization
    for p in loop_permutations:
        for b in block_sizes:
            cmd = [likwid_tool, '-f']
            for g in groups:
                cmd.extend(['-g', g])

            csvpath = f'{out_dir}/{p}_bco_{b}.csv'

            if args.force or not os.path.exists(csvpath):
                output_files.append(csvpath)
                cmd.extend(['-o', csvpath])

                cmd.append(args.executable)
                cmd.extend(['--data', data_input_file])
                cmd.extend(['--count', data_record_count])
                cmd.extend(['--mmloop', p])
                cmd.extend(['--bco', str(b)])
                commands.append(cmd)
            else:
                print(f'Skipping {csvpath} (already exists). Use -f (--force) to force overwrite.')

    for cmd in commands:
        print(f"Running {' '.join(cmd)}")
        p = subprocess.run(cmd)
        print('Process returned ', p.returncode)

    # Write the list of generated filenames to a file
    with open('output_files.txt', 'w') as outfile:
        for f in output_files:
            outfile.write(f + '\n')


if __name__ == '__main__':
    main()
