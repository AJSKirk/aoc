import sys
import termcolor_util as tc
from collections import namedtuple, defaultdict
import itertools


Point = namedtuple('Point', ['x', 'y'])
Instruction = namedtuple('Instruction', ['command_name', 'from_point', 'to_point'])


class Grid(defaultdict):
    def operate(self, instruction, instruction_set):
        x_range = range(instruction.from_point.x, instruction.to_point.x + 1)
        y_range = range(instruction.from_point.y, instruction.to_point.y + 1)

        for x, y in itertools.product(x_range, y_range):
            self[Point(x, y)] = instruction_set[instruction.command_name](self[Point(x, y)])


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
    grid = Grid(bool)
    instruction_set = {
        'turn on': lambda point: True,
        'turn off': lambda point: False,
        'toggle': lambda point: point is False
    }
    for instruction in puzzle_input:
        grid.operate(instruction, instruction_set)
    return sum(1 for point in grid.values() if point)


def part_b(puzzle_input):
    grid = Grid(int)
    instruction_set = {
        'turn on': lambda point: point + 1,
        'turn off': lambda point: max(0, point - 1),
        'toggle': lambda point: point + 2
    }
    for instruction in puzzle_input:
        grid.operate(instruction, instruction_set)
    return sum(point for point in grid.values())


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
