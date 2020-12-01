import sys
import termcolor_util as tc


def load_input(fname):
    with open(fname, 'r') as f:
        return f.read()


def part_a(puzzle_input):
    pass


def part_b(puzzle_input):
    pass


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
