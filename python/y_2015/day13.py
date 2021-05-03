import sys
import re
from collections import defaultdict
import itertools
from typing import Iterable, List


class UndirectedGraph(defaultdict):
    """Extends dict to easily implement bidirectional links with efficient lookups"""
    def __init__(self):
        super().__init__(lambda: defaultdict(int))

    def update_link(self, keys, value):
        for src, dst in itertools.permutations(keys):
            self[src][dst] += value


def score(ordering: List[str], relationships: UndirectedGraph):
    assert len(ordering) == len(relationships)
    # Neat trick for periodic BCs
    pairs = itertools.zip_longest(ordering, ordering[1:], fillvalue=ordering[0])
    return sum(relationships[l][r] for l, r in pairs)


def parse(line: str, relationships: UndirectedGraph):
    pattern = re.compile(r'(\w+) would (\w+) (\d+) happiness units by sitting next to (\w+).')
    subject, sign, magnitude, target = re.match(pattern, line).groups()
    assert sign in ('gain', 'lose')
    value = int(magnitude) * (1 if sign == 'gain' else -1)
    relationships.update_link((subject, target), value)


def brute_force_solve(relationships):
    people = relationships.keys()
    return max(score(ordering, relationships) for ordering in itertools.permutations(people))


def main():
    relationships = UndirectedGraph()
    with open(sys.argv[1], 'r') as f:
        for line in f:
            parse(line, relationships)

    print(brute_force_solve(relationships))
    relationships['Host']  # Sneaky - Initialises host in relationships.keys()
    print(brute_force_solve(relationships))


if __name__ == '__main__':
    main()
