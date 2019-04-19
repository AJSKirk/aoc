import sys
import termcolor_util as tc
from collections import namedtuple, defaultdict
import itertools


Point = namedtuple('Point', ['x', 'y'])


class Instruction(namedtuple('Instruction', ['command_name', 'from_point', 'to_point'])):
    @property
    def command_fn(self):
        if self.command_name == 'turn off':
            return lambda point: False
        if self.command_name == 'turn on':
            return lambda point: True
        if self.command_name == 'toggle':
            return lambda point: point is False  # boolean switch


class Grid(defaultdict):
    def __init__(self):
        super().__init__()
        self.default_factory = bool

    def operate(self, instruction):
        x_range = range(instruction.from_point.x, instruction.to_point.x + 1)
        y_range = range(instruction.from_point.y, instruction.to_point.y + 1)

        for x, y in itertools.product(x_range, y_range):
            self[Point(x, y)] = instruction.command_fn(self[Point(x, y)])


def load_input(fname):
    with open(fname, 'r') as f:
        for line in f:
            yield parse_line(line.strip())


def parse_line(line):
    cmd_and_from_x, from_y_and_to_x, to_y = line.split(',')

    cmd_and_from_x = cmd_and_from_x.split(' ')
    from_x = int(cmd_and_from_x.pop())
    cmd = ' '.join(cmd_and_from_x)

    from_y, _, to_x = from_y_and_to_x.split(' ')
    from_y = int(from_y)
    to_x = int(to_x)

    to_y = int(to_y)

    from_point = Point(from_x, from_y)
    to_point = Point(to_x, to_y)

    return Instruction(cmd, from_point, to_point)


def part_a(puzzle_input):
    grid = Grid()
    for instruction in puzzle_input:
        grid.operate(instruction)
    return sum(1 for point in grid.values() if point)


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
