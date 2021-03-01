from typing import List, Callable, Dict, Iterable
import re
import sys
from collections import namedtuple
import numpy as np

Vector = namedtuple('Vector', ['x', 'y'])


N_DIM = 1000
DIMS = 2
OPERATIONS = ({'turn on': lambda x: 1,
               'turn off': lambda x: 0,
               'toggle': lambda x: x * -1 + 1},
              {'turn on': lambda x: x + 1,
               'turn off': lambda x: np.maximum(x, 1) - 1,  # Max first means don't need to support signed ints
               'toggle': lambda x: x + 2})


def parse(line: str, op_set: Dict) -> (Callable, List[Vector]):
    pattern = r"(.*) (\d+,\d+) through (\d+,\d+)"
    op, *corner_strs = re.match(pattern, line).groups()
    corners = [Vector(*map(int, s.split(','))) for s in corner_strs]
    return op_set[op], corners


def simulate(instructions: Iterable[str], op_set: Dict, dtype=np.byte):
    """Runs simulation. Dtype ended up being unnecessary since all values can be done in a single byte,
    but retained for future extensibility"""
    grid = np.zeros(tuple(N_DIM for _ in range(DIMS)), dtype)
    for line in instructions:
        op, corners = parse(line, op_set)
        # Next two lines are ugly AF, but necessary due to NumPy's python-breaking indexing DSL
        target = grid[corners[0].x:corners[1].x+1, corners[0].y:corners[1].y+1]
        grid[corners[0].x:corners[1].x+1, corners[0].y:corners[1].y+1] = op(target)

    return np.sum(grid)


def main():
    with open(sys.argv[1], 'r') as f:
        for part in range(2):
            f.seek(0)
            print("Total Light Value: {}".format(simulate(f, OPERATIONS[part])))


if __name__ == "__main__":
    main()
