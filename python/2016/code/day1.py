import sys
import termcolor_util as tc
from typing import Tuple

COMPASS = ('North', 'East', 'South', 'West')
Point = Tuple[int, int]


class Agent:
    def __init__(self, x=0, y=0, facing='North'):
        self.x = x
        self.y = y
        self.facing_index = COMPASS.index(facing)
        self.visited = [(0, 0)]

    def turn(self, direction):
        if direction == 'L':
            self.facing_index -= 1
        elif direction == 'R':
            self.facing_index += 1
        else:
            raise ValueError('Invalid direction {}'.format(direction))

        self.facing_index = self.facing_index % len(COMPASS)

    def step(self, steps):
        if self.facing == 'North':
            self.y += steps
        elif self.facing == 'East':
            self.x += steps
        elif self.facing == 'South':
            self.y -= steps
        elif self.facing == 'West':
            self.x -= steps

    def move(self, instruction):
        direction, steps = instruction[0], instruction[1:]
        steps = int(steps)

        self.turn(direction)
        for _ in range(steps):  # Iterate because Part B wants implicit crossings not just turns
            self.step(1)
            self.visited.append(self.location)

    @property
    def facing(self):
        return COMPASS[self.facing_index]

    @property
    def location(self) -> Point:
        return self.x, self.y


def load_input(fname):
    with open(fname, 'r') as f:
        return f.read()


def manhattan_distance(loc1: Point, loc2: Point) -> int:
    return abs(loc1[0] - loc2[0]) + abs(loc1[1] + loc2[1])


def duplicate_items(x: list):
    seen = set()
    dupes = []
    for i in x:
        if i in seen:
            dupes.append(i)
        seen.add(i)

    return dupes


def part_a(instructions):
    agent = Agent()
    for instruction in instructions:
        agent.move(instruction)

    bunny_hq_loc = agent.location
    return manhattan_distance((0, 0), bunny_hq_loc)


def part_b(instructions):
    agent = Agent()
    for instruction in instructions:
        agent.move(instruction)

    bunny_hq_loc = duplicate_items(agent.visited)[0]
    return manhattan_distance((0, 0), bunny_hq_loc)


def main(fname):
    instructions = load_input(fname).split(', ')
    print(f'The Answer to Part A is: {tc.green(part_a(instructions))}')
    print(f'The Answer to Part B is: {tc.green(part_b(instructions))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
