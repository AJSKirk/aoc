from typing import List
import re
import sys
from collections import namedtuple
import numpy as np

Vector = namedtuple('Vector', ['x', 'y'])


N_DIM = 1000
DIMS = 2
OPERATIONS = {'turn on': lambda x: 1,
              'turn off': lambda x: 0,
              'toggle': lambda x: x * -1 + 1}


def parse(line: str) -> (str, List[Vector]):
    pattern = r"(.*) (\d+,\d+) through (\d+,\d+)"
    op, *corner_strs = re.match(pattern, line).groups()
    corners = [Vector(*map(int, s.split(','))) for s in corner_strs]
    return OPERATIONS[op], corners


def main():
    grid = np.zeros(tuple(N_DIM for _ in range(DIMS)), np.byte)
    with open(sys.argv[1], 'r') as f:
        for line in f:
            op, corners = parse(line)
            # Next two lines are ugly AF, but necessary due to NumPy's python-breaking indexing DSL
            target = grid[corners[0].x:corners[1].x+1, corners[0].y:corners[1].y+1]
            grid[corners[0].x:corners[1].x+1, corners[0].y:corners[1].y+1] = op(target)

    print(sum(sum(col for col in row) for row in grid))


if __name__ == "__main__":
    main()
