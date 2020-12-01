import sys
import termcolor_util as tc
from itertools import *


def load_input(fname):
    with open(fname, 'r') as f:
        return [int(line.strip()) for line in f.readlines()]


def powerset(iterable):
    """"Standard itertools recipe"""
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))


def brute_force(containters, target):
    return (comb for comb in powerset(containters) if sum(comb) == 150)


def part_a(containers, target=150):
    return sum(1 for comb in brute_force(containers, target))


def part_b(containers, target=150):
    min_len = min(len(comb) for comb in brute_force(containers, target))
    return sum(1 for comb in brute_force(containers, target) if len(comb) == min_len)


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
