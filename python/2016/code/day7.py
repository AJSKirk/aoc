import sys
import termcolor_util as tc
import itertools


def load_input(fname):
    with open(fname, 'r') as f:
        return f.readlines()


def create_rolling_window(iterable, n=4):
    iters = itertools.tee(iterable, n)
    for i, iter in enumerate(iters):  # Pre-advance
        for j in range(i):
            next(iter)

    return zip(*iters)


def check_abba(window: tuple):
    return window == tuple(reversed(window)) and window[0] != window[1]


def check_tls(address) -> bool:
    windows = create_rolling_window(address, n=4)
    hypernet = False
    has_abba = False

    for window in windows:
        if check_abba(window):
            if hypernet: return False
            else: has_abba = True
        if window[-1] == '[': hypernet = True
        if window[-1] == ']': hypernet = False

    return has_abba


def check_aba_bab(window, mode: str):
    if window[0] == window[2] and window[0] != window[1]:
        if mode.lower() == 'aba': return window
        if mode.lower() == 'bab': return window[1], window[0], window[1]
        else: raise ValueError('Mode must be ABA or BAB')

    return None


def check_ssl(address):
    sets = {'aba': set(), 'bab': set()}
    windows = create_rolling_window(address, n=3)
    mode = 'aba'
    for window in windows:
        sets[mode].add(check_aba_bab(window, mode))
        if window[-1] == '[': mode = 'bab'
        if window[-1] == ']': mode = 'aba'

    sets['aba'].remove(None)
    return len(sets['aba'].intersection(sets['bab'])) > 0


def part_a(puzzle_input):
    count = 0
    for line in puzzle_input:
        if check_tls(line): count += 1

    return count


def part_b(puzzle_input):
    count = 0
    for line in puzzle_input:
        if check_ssl(line): count += 1

    return count


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
