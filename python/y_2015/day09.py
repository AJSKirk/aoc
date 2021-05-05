import sys
import re
import itertools
import functools
from collections import defaultdict
from typing import List


class UndirectedGraph(defaultdict):
    """Extends dict to easily implement bidirectional links with efficient lookups"""
    def __init__(self):
        super().__init__(lambda: defaultdict(int))

    def increment_link(self, keys, value):
        for src, dst in itertools.permutations(keys):
            self[src][dst] += value


def parse(line: str) -> (List[str], int):
    *points, distance = re.match(r'(.*) to (.*) = ([0-9]*)', line).groups()
    return points, int(distance)


def held_karp(graph, compar=min):
    """Memoized recursive implementation of the Held-Karp algorithm by leveraging graph subset solutions"""
    @functools.lru_cache(maxsize=None)
    def subset_cost(subset, final):
        assert final in subset
        if len(subset) == 1:
            return graph[start][final]
        return compar(subset_cost(subset - frozenset((final,)), opt) + graph[opt][final] for opt in subset if opt != final)

    start = list(graph.keys())[0]
    interior = frozenset(graph.keys()) - frozenset((start,))
    return compar(subset_cost(interior, final) + graph[final][start] for final in interior)


def main():
    graph = UndirectedGraph()
    with open(sys.argv[1], 'r') as f:
        for line in f:
            graph.increment_link(*parse(line))

    graph[None]  # Sneaky - Wire a costless path to all other nodes - allows to start and end at different nodes
    print("Shortest Path: {}".format(held_karp(graph)))
    print("Longest Path:  {}".format(held_karp(graph, max)))


if __name__ == "__main__":
    main()
