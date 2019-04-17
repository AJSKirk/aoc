import sys
import termcolor_util as tc
from functools import reduce


class TestString(str):
    def vowel_count(self):
        vowels = 'aeiou'
        return sum(1 for char in self if char in vowels)

    def dupe(self):
        """The reducer sweeps through the string. Dupes get True and get passed down, else it returns the last char

        This may not be most efficient due to no early exit, but it's a nice piece of functional programming"""
        return reduce(lambda c1, c2: True if c1 is True or c1 == c2 else c2, self) is True

    def invalid_comb(self):
        invalids = ('ab', 'cd', 'pq', 'xy')
        return reduce(lambda c1, c2: True if c1 is True or c1 + c2 in invalids else c2, self) is True

    def is_nice_a(self):
        return self.dupe() and (self.vowel_count() >= 3) and (not self.invalid_comb())

    def is_nice_b(self):
        raise NotImplementedError


def load_input(fname):
    with open(fname, 'r') as f:
        for line in f:
            yield TestString(line)


def part_a(puzzle_input):
    return sum(1 for cand in puzzle_input if cand.is_nice_a())


def part_b(puzzle_input):
    pass


def main(fname, loadtype='disk'):
    puzzle_input = load_input(fname)
    if loadtype == 'memory':  # Load input into memory
        puzzle_input = list(puzzle_input)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')

    if loadtype == 'disk':  # Running live generators off disk, need to reinitialize for Part B
        puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt] (disk/memory)')
    else:
        main(*sys.argv[1:])
