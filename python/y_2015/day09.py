import sys
import re
import math
import itertools
from collections import defaultdict
from typing import Tuple, List, Iterable, Set

# Naive approach was getting 400ms to benchmark


class UndirectedGraph(defaultdict):
    """Extends dict to automatically handle pairs of points regardless of order, and handle invalid links"""
    def __init__(self):
        super().__init__(dict)

    def add_link(self, keys, value):
        for src, dst in itertools.permutations(keys):
            self[src][dst] = value


def parse(line: str) -> (List[str], int):
    *points, distance = re.match(r'(.*) to (.*) = ([0-9]*)', line).groups()
    return points, int(distance)


def held_karp():
    pass


def lin_kernighan():
    pass


def naive(graph: UndirectedGraph, visited, distance=0):
    if len(visited) == len(graph):  # Recursion base case
        return distance

    current = visited[-1]
    options = (opt for opt in graph[current].keys() if opt not in visited)

    return min(naive(graph, visited + (option,), distance + graph[current][option]) for option in options)


def main():
    graph = UndirectedGraph()
    with open(sys.argv[1], 'r') as f:
        for line in f:
            graph.add_link(*parse(line))

    print(min(naive(graph, (start,)) for start in graph.keys()))


if __name__ == "__main__":
    main()
