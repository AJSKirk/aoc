import sys
import termcolor_util as tc
from collections import defaultdict


def load_input(fname):
    paths = defaultdict(dict)
    with open(fname, 'r') as f:
        for line in f:
            start, _, end, _, dist = line.strip().split(' ')
            paths[start][end] = int(dist)
            paths[end][start] = int(dist)  # Hacky symmetric dict
    return paths


def path_recurse(paths, hist=[], dist=0, fn=min):
    cities = set(paths.keys())
    if len(hist) == len(cities):
        return dist

    current_city = hist[-1]
    options = [city for city in paths[current_city].keys() if city not in hist]
    cand_dists = [path_recurse(paths, hist + [cand], dist + paths[current_city][cand], fn=fn) for cand in options]
    cand_dists = [x for x in cand_dists if x]  # Filter out nones
    return fn(cand_dists) if cand_dists else None


def part_a(paths):
    seeds = [city for city in paths.keys()]
    seed_dists = [x for x in [path_recurse(paths, [seed]) for seed in seeds] if x]
    return min(seed_dists)


def part_b(paths):
    seeds = [city for city in paths.keys()]
    seed_dists = [x for x in [path_recurse(paths, [seed], fn=max) for seed in seeds] if x]
    return max(seed_dists)


def main(fname, loadtype='disk'):
    puzzle_input = load_input(fname)
    if loadtype == 'memory':  # Load input into memory
        puzzle_input = list(puzzle_input)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')

    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt] (disk/memory)')
    else:
        main(*sys.argv[1:])
