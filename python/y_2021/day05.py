import sys
from itertools import combinations, chain, zip_longest
from typing import NamedTuple, Tuple, Iterable, Set
import operator as op



N_DIMS = 2
Point = Tuple[int, int]


class Line(NamedTuple):
    start: Point
    end: Point

    @property
    def straight_dim(self):
        try:
            return tuple(s == e for s, e in zip(*self)).index(1)
        except ValueError:
            return -1

    def min_index(self, dimension):
        return min(self.start[dimension], self.end[dimension])

    def max_index(self, dimension):
        return max(self.start[dimension], self.end[dimension])

    def points(self):
        shortest_dim = min((dim for dim in range(N_DIMS)), key=lambda dim: self.max_index(dim) - self.min_index(dim))
        return zip_longest(*(range(self.min_index(dim), range(self.max_index(dim))) for dim in range(N_DIMS)),
                           fillvalue=self.max_index(shortest_dim))


def parse_line(line: str) -> Line:
    return Line(*(tuple(int(el) for el in pt.split(',')) for pt in line.strip().split(' -> ')))


def intersecting_points(lines):  # Needs to yield a list of overlappying points to avoid double counting
    for dim in range(N_DIMS):
        if len(set(point[dim] for line in lines for point in line)) == 1:  # Aligned in same plane
            start = max(line.min_index(1 - dim) for line in lines)
            end = min(line.max_index(1 - dim) for line in lines)
            for idx in range(start, end + 1):
                out = [0, 0]
                out[dim] = lines[0].start[dim]  # All the same anyway
                out[1 - dim] = idx
                yield tuple(out)

        if not any(line.straight_dim == -1 for line in lines):  # Both horiz/vert
            # Test for intersection - WLOG because we get the reverse when we come around for the other dimension
            if lines[0].straight_dim == dim != lines[1].straight_dim:
                if lines[1].min_index(dim) <= lines[0].start[dim] <= lines[1].max_index(dim):  # Planes cross
                    if lines[0].min_index(1 - dim) <= lines[1].start[1 - dim] <= lines[0].max_index(1 - dim):
                        out = [0, 0]
                        out[dim] = lines[0].start[dim]
                        out[1 - dim] = lines[1].start[1 - dim]
                        yield tuple(out)




    return


def all_intersects(line_set: Iterable[Line]) -> Set[Point]:
    return set(chain(*(intersecting_points(pair) for pair in combinations(line_set, 2))))


def main():
    lines = [parse_line(line) for line in sys.stdin]
    #lines = [parse_line(line) for line in open('f.txt')]
    straight_lines = (line for line in lines if line.straight_dim != -1)

    print(f"Total Straight Line Intersections: {len(all_intersects(straight_lines))}")
    print(f"Total Line Intersections: {len(all_intersects(lines))}")


if __name__ == "__main__":
    main()
