import sys
import termcolor_util as tc
from collections import namedtuple
from functools import reduce
import operator


class Gift(namedtuple('Gift', ['l', 'w', 'h'])):
    def smallest_side_area(self):
        edges = sorted(self)[:2]  # namedtuple has an __iter__() method
        return reduce(operator.mul, edges)  # Easy scale to more dimensions

    def paper_req(self):
        area = 2 * (self.l * self.w + self.w * self.h + self.h * self.l)
        return area + self.smallest_side_area()

    def bow_size(self):
        return reduce(operator.mul, self)  # Easy scale to more dimensions

    def smallest_perim(self):
        edges = sorted(self)[:2]
        return 2 * reduce(operator.add, edges)

    def ribbon_req(self):
        return self.smallest_perim() + self.bow_size()


def load_input(fname):
    with open(fname, 'r') as f:
        for line in f:
            yield Gift(*[int(dim) for dim in line.split('x')])


def part_a(puzzle_input):
    return sum(gift.paper_req() for gift in puzzle_input)


def part_b(puzzle_input):
    return sum(gift.ribbon_req() for gift in puzzle_input)


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
