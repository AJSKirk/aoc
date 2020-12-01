import sys
import termcolor_util as tc
from collections import Counter, defaultdict


def load_input(fname):
    with open(fname, 'r') as f:
        return pivot(f.readlines())


def pivot(rows):
    cols = defaultdict(list)
    for row in rows:
        for pos, val in enumerate(row):
            cols[pos].append(val)

    for colnum in sorted(cols.keys()):
        yield cols[colnum]


def decode(line, mode='most'):
    count = Counter(line)
    targets = {'most': 0, 'least': -1}
    try:
        target = targets[mode]
    except KeyError:
        raise Exception('Invalid mode suuplied. Use "most" or "least" only.')

    return count.most_common()[target][0]


def part_a(puzzle_input):
    return ''.join(decode(line, 'most') for line in puzzle_input)


def part_b(puzzle_input):
    return ''.join(decode(line, 'least') for line in puzzle_input)


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
