import argparse
import subprocess


def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('executable', help='The executable to be run')
    parser.add_argument('-o', '--output', help='Specify the output directory')
    parser.add_argument('-f', '--force', action='store_true', help='Overwrite existing file')

    return parser.parse_args()


def main():

    args = parse_args()

    data_input_file = '../data/movie_reviews_combined.txt'
    data_record_count = '1000'

    loop_permutations = ['ijk', 'ikj', 'jik', 'jki', 'kij', 'kji']
    block_sizes = [0, 16, 32, 64, 128, 256, 512, 1024, 2048]

    base_args = [f'./{args.executable}', '--data', data_input_file, '--count', data_record_count]

    print('Loop,Block Size,Runtime (s)')
    for loop in loop_permutations:
        for size in block_sizes:

            args = []
            args.extend(base_args)

            args.extend(['--mmloop', loop])
            if size > 0:
                args.extend(['--bco', str(size)])

            print(','.join((loop, str(size))), end=',')
            command = ' '.join(args)
            p = subprocess.run(command, shell=True)


if __name__ == '__main__':
    main()
