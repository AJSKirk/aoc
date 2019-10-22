import sys
import termcolor_util as tc
from itertools import permutations, chain, islice, count


def load_input(fname):
    with open(fname, 'r') as f:
        return f.readlines()


def valid_triangle(sides):
    def valid_combo(combo):
        return combo[0] + combo[1] - combo[2] > 0

    return all(valid_combo(combo) for combo in permutations(sides))


def part_a(puzzle_input):
    triangles = [(int(i) for i in row.strip().split()) for row in puzzle_input]
    return sum(valid_triangle(sides) for sides in triangles)


def part_b(puzzle_input):
    cols = ([], [], [])
    for row in puzzle_input:
        parsed_row = row.strip().split()
        for col, val in zip(cols, parsed_row):
            col.append(val)

    stream = chain(*cols)

    def chunks(stream, n):
        return iter(lambda: tuple(int(i) for i in islice(stream, n)), ())

    return sum(valid_triangle(chunk) for chunk in chunks(stream, 3))


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
