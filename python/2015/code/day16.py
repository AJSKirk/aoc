import sys
import termcolor_util as tc


def load_input(fname):
    out = {}
    with open(fname, 'r') as f:
        for line in f.readlines():
            delim = line.find(':')
            suenum = line[:delim]
            facts = line.strip()[delim + 2:]
            out[suenum] = dict(fact.split(': ') for fact in facts.split(', '))
    return out


def part_a(sues):
    knowns = {
        'children': 3,
        'cats': 7,
        'samoyeds': 2,
        'pomeranians': 3,
        'akitas': 0,
        'vizslas': 0,
        'goldfish': 5,
        'trees': 3,
        'cars': 2,
        'perfumes': 1
    }
    while len(sues) > 1:
        for k, v in knowns.items():
            sues = {sue: sdict for sue, sdict in sues.items() if int(sdict.get(k, v)) == v}
    return sues


def part_b(sues):
    knowns = {
        'children': lambda x: x == 3 or x == -1,
        'cats': lambda x: x > 7 or x == -1,
        'samoyeds': lambda x: x == 2 or x == -1,
        'pomeranians': lambda x: x < 3 or x == -1,
        'akitas': lambda x: x == 0 or x == -1,
        'vizslas': lambda x: x == 0 or x == -1,
        'goldfish': lambda x: x < 5 or x == -1,
        'trees': lambda x: x > 3 or x == -1,
        'cars': lambda x: x == 2 or x == -1,
        'perfumes': lambda x: x == 1 or x == -1
    }
    while len(sues) > 1:
        for k, v in knowns.items():
            sues = {sue: sdict for sue, sdict in sues.items() if v(int(sdict.get(k, -1)))}
    return sues


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
