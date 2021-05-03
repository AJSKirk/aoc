import sys
import re
from collections import defaultdict
import itertools
from typing import List
import functools


class UndirectedGraph(defaultdict):
    """Extends dict to easily implement bidirectional links with efficient lookups"""
    def __init__(self):
        super().__init__(lambda: defaultdict(int))

    def update_link(self, keys, value):
        for src, dst in itertools.permutations(keys):
            self[src][dst] += value


def parse(line: str, relationships: UndirectedGraph):
    pattern = re.compile(r'(\w+) would (\w+) (\d+) happiness units by sitting next to (\w+).')
    subject, sign, magnitude, target = re.match(pattern, line).groups()
    assert sign in ('gain', 'lose')
    value = int(magnitude) * (1 if sign == 'gain' else -1)
    relationships.update_link((subject, target), value)


def held_karp(graph, compar=min):
    """Going around the table *is the travelling salesman problem*. Slight modification to Day 9 solution to handle
    the perdiodic boundary conditions"""
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
    relationships = UndirectedGraph()
    with open(sys.argv[1], 'r') as f:
        for line in f:
            parse(line, relationships)

    print(held_karp(relationships, compar=max))
    relationships['Host']  # Sneaky - Initialises host in relationships.keys()
    print(held_karp(relationships, compar=max))


if __name__ == '__main__':
    main()
