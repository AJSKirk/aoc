from typing import Tuple
import itertools
import operator
from functools import reduce
import sys


Box = Tuple[int]


def box_parser(line: str) -> Box:
    return tuple(sorted(int(v) for v in line.strip().split('x')))


def paper_required(box: Box) -> int:
    surface_area = sum(i * j for i, j in itertools.permutations(box, 2))
    smallest_area = box[0] * box[1]  # Take advantage of sort in parser
    return surface_area + smallest_area


def ribbon_required(box: Box) -> int:
    smallest_perim = 2 * (box[0] + box[1])
    bow = reduce(operator.mul, box)
    return smallest_perim + bow


def main():
    with open(sys.argv[1], 'r') as f:
        boxes = [box_parser(line) for line in f.readlines()]

    print("Total wrapping paper required: {}".format(sum(paper_required(box) for box in boxes)))
    print("Total ribbon required: {}".format(sum(ribbon_required(box) for box in boxes)))


if __name__ == "__main__":
    main()
