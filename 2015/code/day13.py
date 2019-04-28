import sys
import termcolor_util as tc
import itertools
from collections import defaultdict


def load_input(fname):
    prefs = defaultdict(lambda:defaultdict(int))  # People -> Person[Neighbour]: Happiness
    multiplier = {'gain': 1, 'lose': -1}
    with open(fname, 'r') as f:
        for line in f:
            person, _, change, units, *_, neighbour = line.strip()[:-1].split(' ')  # Star-unpacking is a cool trick
            prefs[person][neighbour] = multiplier[change] * int(units)
    return prefs


def score(arrangement, prefs):
    out = 0
    for i, person in enumerate(arrangement):
        left_neighbour = arrangement[i-1]
        right_neighbour = arrangement[(i+1) % len(arrangement)]
        out += prefs[person][left_neighbour] + prefs[person][right_neighbour]

    return out


def best_arrangement(prefs):
    people = list(prefs.keys())
    first = people.pop()  # Fixed reference to exploit without loss of generality
    return max(score((first,) + tail_permute, prefs) for tail_permute in itertools.permutations(people))


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(best_arrangement(puzzle_input))}')
    puzzle_input['Me'] = defaultdict(int)
    print(f'The Answer to Part B is: {tc.green(best_arrangement(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(*sys.argv[1:])
