import sys
import termcolor_util as tc
from itertools import *
import primefactors
from functools import reduce
from operator import mul
import math


def star_mul(xs):
    """Return product of a list"""
    return reduce(mul, xs) if len(xs) > 0 else 0  # Catch the empty set


def powerset(iterable):
    """"Standard itertools recipe"""
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s) + 1))


def get_factors(n, tire_out=math.inf):
    primes = primefactors.factorize(n)
    factors = set(star_mul(combo) for combo in powerset(primes))
    factors.add(1)
    return set(i for i in factors if n <= i * tire_out)


def part_a(puzzle_input):
    return next(n for n in count(1) if sum(10 * i for i in get_factors(n)) >= puzzle_input)


def part_b(puzzle_input):
    return next(n for n in count(1) if sum(11 * i for i in get_factors(n, 50)) >= puzzle_input)


def main(score_thresh):
    print(f'The Answer to Part A is: {tc.green(part_a(score_thresh))}')
    print(f'The Answer to Part B is: {tc.green(part_b(score_thresh))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(int(sys.argv[1]))
