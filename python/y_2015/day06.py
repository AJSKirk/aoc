from typing import Tuple
import re
import sys
import operator
from functools import reduce


Point = Tuple[int, int]
LineSegment = Tuple[Point, Point]
CornerSet = Tuple[LineSegment, LineSegment]


class Zone:
    def __init__(self, op, *corners):
        self.ops = [op]  # Storing op-chain instead of current value avoids rework in Part 2
        self.corners = corners

    def resolve(self) -> int:
        pass

    def resolve_brightness(self) -> int:
        pass

    @property
    def area(self):
        return reduce(operator.mul, (abs(start - end) for start, end in self.corners))


def parse(line: str) -> Zone:
    pattern = r"(.*) (\d+,\d+) through (\d+,\d+)"
    op, *corner_strs = re.match(pattern, line).groups()
    corners = [tuple(map(int, s.split(','))) for s in corner_strs]
    return Zone(op, corners)


def main():
    current_zones = [Zone('turn off', ())]  # Instantiate a dummy zone
    with open(sys.argv[1], 'r') as f:
        for line in f:
            new_rect = parse(line)
            new_zones = []
            for rect in current_zones:


if __name__ == "__main__":
    main()
