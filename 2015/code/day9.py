import sys
import termcolor_util as tc
from collections import defaultdict

class ListItem(str):
    @property
    def codelen(self):
        return len(self)

    @property
    def charlen(self):
        return len(eval(self))

    @property
    def enclen(self):
        slashes = self.count('\\')
        quotes = self.count('"')
        return self.codelen + slashes + quotes + 2


def load_input(fname):
    paths = defaultdict(dict)
    with open(fname, 'r') as f:
        for line in f:
            start, _, end, _, dist = line.strip().split(' ')
            paths[start][end] = int(dist)
    return paths


def part_a(paths):
    cities = set(paths.keys()) | set(to_city for from_city in paths.values() for to_city in from_city.keys())


def part_b(puzzle_input):
    pass


def main(fname, loadtype='disk'):
    puzzle_input = load_input(fname)
    if loadtype == 'memory':  # Load input into memory
        puzzle_input = list(puzzle_input)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')

    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt] (disk/memory)')
    else:
        main(*sys.argv[1:])
