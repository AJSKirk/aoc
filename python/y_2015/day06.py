from typing import Tuple, List
import re
import sys
from collections import namedtuple


Vector = namedtuple('Vector', ['x', 'y'])


N_DIM = 1000
OPERATIONS = {'turn on': lambda x: 1,
              'turn off': lambda x: 0,
              'toggle': lambda x: int(not x)}


def parse(line: str) -> (str, List[Vector]):
    pattern = r"(.*) (\d+,\d+) through (\d+,\d+)"
    op, *corner_strs = re.match(pattern, line).groups()
    corners = [Vector(*map(int, s.split(','))) for s in corner_strs]
    return OPERATIONS[op], corners


def main():
    grid = [[0 for _ in range(N_DIM)] for _ in range(N_DIM)]
    with open(sys.argv[1], 'r') as f:
        for line in f:
            op, corners = parse(line)
            for row in range(corners[0].x, corners[1].x + 1):
                for col in range(corners[0].y, corners[1].y + 1):
                    grid[row][col] = op(grid[row][col])

    print(sum(sum(col for col in row) for row in grid))


if __name__ == "__main__":
    main()
