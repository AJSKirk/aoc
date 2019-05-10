import sys
import termcolor_util as tc
from collections import namedtuple, deque
import re
import math


Operation = namedtuple('Operation', ['frm', 'to'])


def load_input(fname):
    with open(fname, 'r') as f:
        lines = f.readlines()
        operations = set(Operation(*line.strip().split(' => ')) for line in lines if '=>' in line)
        molecule = lines[-1].strip()

    return operations, molecule


def possible_steps(operations, molecule):
    results = set()
    for op in operations:
        for match in re.finditer(op.frm, molecule):
            results.add(molecule[:match.start()] + op.to + molecule[match.end():])

    return results


def part_a(operations, molecule):
    return len(possible_steps(operations, molecule))


def dijkstra(operations, target_molecule, start_molecule='e'):
    """Going to use a simplified (don't care about path) Dijkstra implementation"""
    distances = {start_molecule: 0}
    spent = set()

    while True:
        for mol in spent:  # Clear stuff we've already fully considered
            distances.pop(mol, None)

        current_molecule, current_dist = min(distances.items(), key=lambda x: x[1])

        neighbours = set()
        for op in operations:
            for match in re.finditer(op.frm, current_molecule):
                neighbour = current_molecule[:match.start()] + op.to + current_molecule[match.end():]
                if neighbour == target_molecule:
                    return current_dist + 1
                neighbours.add(neighbour)

        spent.add(current_molecule)
        neighbours.difference_update(spent)  # Drop anything we've exhausted

        for neighbour in neighbours:
            distances[neighbour] = min(distances.get(neighbour, math.inf), current_dist + 1)


def BFS(operations, target_molecule, source='e'):
    queue = deque(source)
    dists = {source: 0}

    while queue:
        cand = queue.popleft()
        if cand == target_molecule:
            return dists[cand]
        for neighbour in possible_steps(operations, cand):
            if neighbour not in dists:
                queue.append(neighbour)
                dists[neighbour] = dists[cand] + 1


def part_b(operations, target_molecule):
    return BFS(operations, target_molecule)


def main(fname):
    operations, molecule = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(operations, molecule))}')
    print(f'The Answer to Part B is: {tc.green(part_b(operations, molecule))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
