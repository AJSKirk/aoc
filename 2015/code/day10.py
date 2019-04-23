import sys
import termcolor_util as tc
from functools import reduce


def look_and_say(sequence):
    out = ''
    running = 0
    current = ''
    for char in sequence:
        if char == current:
            running += 1
        else:
            out += str(running) + current
            current = char
            running = 1

    return out[1:] + str(running) + current  # Drop initial zero


def part_a(sequence):
    return len(reduce(lambda a, b: look_and_say(a), range(40), sequence))  # Iterator is better, but this seemed fun


def part_b(sequence):
    return len(reduce(lambda a, b: look_and_say(a), range(50), sequence))


def main(sequence):
    print(f'The Answer to Part A is: {tc.green(part_a(sequence))}')
    print(f'The Answer to Part B is: {tc.green(part_b(sequence))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [sequence]')
    else:
        main(*sys.argv[1:])
