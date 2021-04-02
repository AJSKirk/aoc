import sys
import re
import itertools
import functools
from collections import defaultdict
from typing import List


class UndirectedGraph(defaultdict):
    """Extends dict to easily implement bidirectional links with efficient lookups"""
    def __init__(self):
        super().__init__(dict)

    def add_link(self, keys, value):
        for src, dst in itertools.permutations(keys):
            self[src][dst] = value


def parse(line: str) -> (List[str], int):
    *points, distance = re.match(r'(.*) to (.*) = ([0-9]*)', line).groups()
    return points, int(distance)


def held_karp(graph):
    """Memoized recursive implementation of the Held-Karp algorithm by leveraging graph subset solutions"""
    @functools.lru_cache(maxsize=None)
    def subset_cost(subset, final):
        assert final in subset
        if len(subset) == 1:
            return 0
        return min(subset_cost(subset - frozenset((final,)), opt) + graph[opt][final] for opt in subset if opt != final)

    return min(subset_cost(frozenset(graph.keys()), node) for node in graph.keys())


def main():
    graph = UndirectedGraph()
    with open(sys.argv[1], 'r') as f:
        for line in f:
            graph.add_link(*parse(line))

    print("Shortest Path: {}".format(held_karp(graph)))


if __name__ == "__main__":
    main()
