import sys
import termcolor_util as tc
from collections import namedtuple, defaultdict
import itertools


class Wire:
    def __init__(self, func_text, wires):
        #self.name = name
        self.wires = wires
        self.val = None
        func_text = func_text.split(' ')

        two_op_funcs = {
            'AND': lambda x, y: x & y,
            'OR': lambda x, y: x | y,
            'LSHIFT': lambda x, y: x << y,
            'RSHIFT': lambda x, y: x >> y,
        }

        if len(func_text) == 1:
            self.func = lambda: self.wires.pull(func_text[0])  # Trick to force early-binding of lambda fn
        elif func_text[0] == 'NOT':
            self.func = lambda: 0xffff - self.wires.pull(func_text[1])  # Unsigned bitwise not
        else:
            self.func = lambda: two_op_funcs[func_text[1]](self.wires.pull(func_text[0]), self.wires.pull(func_text[2]))

    @property
    def value(self):
        if not self.val:
            self.val = self.func()  # Memoize for efficiency
        return self.val


class Wires(dict):
    def pull(self, key):
        return int(key) if key.isdecimal() else self[key].value


def load_input(fname):
    wires = Wires()
    with open(fname, 'r') as f:
        for line in f:
            func_text, name = line.strip().split(' -> ')
            wires[name] = Wire(func_text, wires)

    return wires


def part_a(puzzle_input):
    return puzzle_input.pull('a')


def part_b(puzzle_input):
    pass

def main(fname, loadtype='disk'):
    puzzle_input = load_input(fname)
    if loadtype == 'memory':  # Load input into memory
        puzzle_input = list(puzzle_input)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')

    if loadtype == 'disk':  # Running live generators off disk, need to reinitialize for Part B
        puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt] (disk/memory)')
    else:
        main(*sys.argv[1:])
