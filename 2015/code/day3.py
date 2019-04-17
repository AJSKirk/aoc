import sys
import termcolor_util as tc
from collections import defaultdict
from itertools import cycle


class Location:
    def __init__(self):
        self.x = 0
        self.y = 0

    def to_tuple(self):
        return self.x, self.y

    def move(self, direction):
        if direction == '^':
            self.y += 1
        elif direction == 'v':
            self.y -= 1
        elif direction == '>':
            self.x += 1
        elif direction == '<':
            self.x -= 1
        else:
            raise ValueError(f'Invalid Direction "{direction}" provided to move method"')


def load_input(fname):
    with open(fname, 'r') as f:
        return f.read()


def part_a(puzzle_input):
    loc = Location()
    houses = defaultdict(int)
    houses[loc.to_tuple()] += 1  # Present to initial house

    for direction in puzzle_input:
        loc.move(direction)
        houses[loc.to_tuple()] += 1

    return len(houses)


def part_b(puzzle_input, n_santas=2):
    locs = [Location() for _ in range(n_santas)]
    print(locs)
    houses = defaultdict(int)
    houses[locs[0].to_tuple()] += 1
    houses[locs[1].to_tuple()] += 1

    for direction, santa in zip(puzzle_input, cycle(locs)):
        santa.move(direction)
        houses[santa.to_tuple()] += 1

    return len(houses)


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
