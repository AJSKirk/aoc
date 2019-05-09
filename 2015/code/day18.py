import sys
import termcolor_util as tc
from collections import namedtuple
import numpy as np
import itertools


Point = namedtuple('Point', ['row', 'col'])


def load_input(fname, size=100):
    grid = np.zeros((size, size), dtype=bool)
    with open(fname, 'r') as f:
        for row, line in enumerate(f.readlines()):
            for col, cell in enumerate(line.strip()):
                grid[row][col] = cell == '#'
    return grid


def neighbours(point, size=100):
    rows = range(max(point.row - 1, 0), min(point.row + 2, size))
    cols = range(max(point.col - 1, 0), min(point.col + 2, size))

    return (Point(row, col) for row in rows for col in cols if not (row == point.row and col == point.col))


def stepcell(point, grid):
    n_on = sum(grid[n.row][n.col] for n in neighbours(point, grid.shape[0]))
    if grid[point.row][point.col] == np.False_:
        return n_on == 3
    else:
        return n_on in (2, 3)


def step(grid):
    newgrid = grid.copy()
    for row, col in itertools.product(range(grid.shape[0]), repeat=2):
        newgrid[row][col] = stepcell(Point(row, col), grid)
    return newgrid


def print_grid(grid):
    """Useful for diagnostics"""
    for line in grid:
        print(''.join('#' if cell else '.' for cell in line))
    print('-' * grid.shape[0])


def part_a(grid, steps):
    for i in range(steps):
        grid = step(grid)
        # print(f'After Step {i} - {np.sum(grid)}')  # Cellular automata often loop, let's keep an eye out for that

    return np.sum(grid)


def part_b(grid, steps):
    corners = list(itertools.product((0, grid.shape[0] - 1), repeat=2))
    for i in range(steps):
        for row, col in corners:
            grid[row][col] = True  # Manually refix at each step
        grid = step(grid)
        # print(f'After Step {i} - {np.sum(grid)}')  # Cellular automata often loop, let's keep an eye out for that

    for row, col in corners:
        grid[row][col] = True
    return np.sum(grid)


def main(fname):
    puzzle_input = load_input(fname, size=100)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input, steps=100))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input, steps=100))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
