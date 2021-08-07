import sys
import numpy as np
import itertools
from typing import IO, Union


NUM_STEPS = 100

Grid = np.ndarray


def parse(file: Union[IO, str]) -> Grid:
    """Parse file into 2D boolean numpy array"""
    raw = np.fromfile(file, sep='', dtype=np.byte)
    grid = (raw[raw != ord('\n')] - ord('.')).astype(bool)  # Remove newlines and cast to bool
    # Reshape and halo
    grid = grid.reshape(int(np.sqrt(grid.size)), -1)
    grid = np.pad(grid, ((1, 1), (1, 1)), constant_values=0)
    return grid


def step(grid: Grid) -> Grid:
    tot = sum(np.roll(grid, shift, axis=(0, 1)) for shift in filter(any, itertools.product(range(-1, 2), repeat=2)))
    grid[grid & ~np.isin(tot, (2, 3))] = False
    grid[~grid & (tot == 3)] = True

    grid[0, :] = grid[-1, :] = grid[:, 0] = grid[:, -1] = False  # Rezero halo
    return grid


def force_corners(grid: Grid) -> Grid:
    for corner in itertools.product((-2, 1), repeat=2):  # Account for Halo
        grid[corner] = True
    return grid


def main():
    with open(sys.argv[1], 'r') as f:
        grid = parse(f)

    forced_grid = grid.copy()

    for _ in range(NUM_STEPS):
        grid = step(grid)

    print("Lights on: {}".format(np.sum(grid)))

    for _ in range(NUM_STEPS):
        forced_gridgrid = force_corners(forced_grid)
        forced_grid = step(forced_grid)

    forced_grid = force_corners(forced_grid)
    print("Lights on with forcing: {}".format(np.sum(forced_grid)))


if __name__ == "__main__":
    main()
