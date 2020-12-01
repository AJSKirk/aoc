import sys
import termcolor_util as tc
import re

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
    with open(fname, 'r') as f:
        for line in f:
            yield(ListItem(line.strip()))


def part_a(puzzle_input):
    return sum(item.codelen - item.charlen for item in puzzle_input)


def part_b(puzzle_input):
    return sum(item.enclen - item.codelen for item in puzzle_input)


def main(fname, loadtype='disk'):
    puzzle_input = load_input(fname)
    if loadtype == 'memory':  # Load input into memory
        puzzle_input = list(puzzle_input)
    a_ans = part_a(puzzle_input)
    print(f'The Answer to Part A is: {tc.green(a_ans)}')

    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt] (disk/memory)')
    else:
        main(*sys.argv[1:])
