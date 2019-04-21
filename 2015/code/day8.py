import sys
import termcolor_util as tc
import re

class ListItem(str):
    @property
    def codelen(self):
        slashes = self.count(r'\\')
        return len(self)  # Because python adds slashes to escape the escape slashes

    @property
    def charlen(self):
        char_rep = self
        no_slashes = re.sub(r'\\\\', ' ', char_rep)  # Manually parse each to avoid collisions
        no_quotes = re.sub(r'\\"', ' ', no_slashes)
        no_hexes = re.sub(r'\\x[0-9a-f][0-9a-f]', ' ', no_quotes)
        return len(no_hexes) - 2


def load_input(fname):
    with open(fname, 'r') as f:
        for line in f:
            yield(ListItem(line.strip()))


def part_a(puzzle_input):
    return sum(item.codelen - item.charlen for item in puzzle_input)


def part_b(puzzle_input, fix):
    pass


def main(fname, loadtype='disk'):
    puzzle_input = load_input(fname)
    if loadtype == 'memory':  # Load input into memory
        puzzle_input = list(puzzle_input)
    a_ans = part_a(puzzle_input)
    print(f'The Answer to Part A is: {tc.green(a_ans)}')

    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input, a_ans))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt] (disk/memory)')
    else:
        main(*sys.argv[1:])
