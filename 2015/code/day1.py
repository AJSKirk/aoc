import sys
import termcolor_util as tc


def load_input(fname):
    with open(fname, 'r') as f:
        return f.read()


def part_a(puzzle_input):
    pos = 0
    for char in puzzle_input:
        pos += directions[char]

    return pos


def part_b(puzzle_input):
    pos = 0
    for i, char in enumerate(puzzle_input, start=1):
        pos += directions[char]
        if pos < 0:
            return i


def main(fname):
    puzzle_input = load_input(fname)
    directions = {'(': 1, ')': -1}
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part A is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
