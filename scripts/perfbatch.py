#!/usr/bin/env python3

import subprocess
import os


exe_dir = '../build'

def main():

    out_dir = os.path.join(exe_dir, 'L3')

    if not os.path.exists(out_dir):
        os.mkdir(out_dir)

    exe_base = '../build/LTS'
    likwid_tool = 'likwid-perfctr' 
    data_input_file = '../data/movie_reviews_combined.txt' 
    data_record_count = '1000'

    groups = ['L3']
    loop_permutations = ['ijk', 'ikj', 'jik', 'jki', 'kij', 'kji']

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
        output_files.append(csvpath)
        cmd.extend(['-o', csvpath])

        cmd.append(exe_base)
        cmd.extend(['--data', data_input_file])
        cmd.extend(['--count', data_record_count])
        cmd.extend(['--mmloop', p])
        commands.append(cmd)

    # Run all loop permutations with block-copy optimization, block size = 256
    for p in loop_permutations:
        cmd = [likwid_tool, '-f']
        for g in groups:
            cmd.extend(['-g', g])
        
        blocksize = 256

        csvpath = f'{out_dir}/{p}_bco_{blocksize}.csv'
        output_files.append(csvpath)
        cmd.extend(['-o', csvpath])

        cmd.append(exe_base)
        cmd.extend(['--data', data_input_file])
        cmd.extend(['--count', data_record_count])
        cmd.extend(['--mmloop', p])
        cmd.extend(['--bco', str(blocksize)])
        commands.append(cmd)

    # Run all loop permutations with block-copy optimization, block size = 512
    for p in loop_permutations:
        cmd = [likwid_tool, '-f']
        for g in groups:
            cmd.extend(['-g', g])
        
        blocksize = 512

        csvpath = f'{out_dir}/{p}_bco_{blocksize}.csv'
        cmd.extend(['-o', f'{out_dir}/{p}_bco_{blocksize}.csv'])
        output_files.append(csvpath)

        cmd.append(exe_base)
        cmd.extend(['--data', data_input_file])
        cmd.extend(['--count', data_record_count])
        cmd.extend(['--mmloop', p])
        cmd.extend(['--bco', str(blocksize)])
        commands.append(cmd)

    # Run all loop permutations with block-copy optimization, block size = 1024
    for p in loop_permutations:
        cmd = [likwid_tool, '-f']
        for g in groups:
            cmd.extend(['-g', g])
        
        blocksize = 1024

        csvpath = f'{out_dir}/{p}_bco_{blocksize}.csv'
        cmd.extend(['-o', f'{out_dir}/{p}_bco_{blocksize}.csv'])
        output_files.append(csvpath)

        cmd.append(exe_base)
        cmd.extend(['--data', data_input_file])
        cmd.extend(['--count', data_record_count])
        cmd.extend(['--mmloop', p])
        cmd.extend(['--bco', str(blocksize)])
        commands.append(cmd)

    # Run all loop permutations with block-copy optimization, block size = 1024
    for p in loop_permutations:
        cmd = [likwid_tool, '-f']
        for g in groups:
            cmd.extend(['-g', g])
        
        blocksize = 2048

        csvpath = f'{out_dir}/{p}_bco_{blocksize}.csv'
        cmd.extend(['-o', f'{out_dir}/{p}_bco_{blocksize}.csv'])
        output_files.append(csvpath)

        cmd.append(exe_base)
        cmd.extend(['--data', data_input_file])
        cmd.extend(['--count', data_record_count])
        cmd.extend(['--mmloop', p])
        cmd.extend(['--bco', str(blocksize)])
        commands.append(cmd)


    for cmd in commands:
        print(f"Running {' '.join(cmd)}")
        subprocess.run(cmd)

    # Write the list of generated filenames to a file
    with open('output_files.txt', 'w') as outfile:
        for f in output_files:
            outfile.write(f + '\n')


if __name__ == '__main__':
    main()
