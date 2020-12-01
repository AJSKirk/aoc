import sys
import termcolor_util as tc
import re
import json


def load_input(fname):
    with open(fname, 'r') as f:
        return f.read().strip()


def recurse_items(json_obj):
    if type(json_obj) == int:
        return json_obj
    if type(json_obj) == dict:
        if 'red' in json_obj.values():
            return 0
        else:
            return sum(recurse_items(child) for child in json_obj.values())
    elif type(json_obj) == list:
        return sum(recurse_items(child) for child in json_obj)
    else:
        return 0


def part_a(puzzle_input):
    numbers = (int(x) for x in re.findall(r'-?[0-9]+', puzzle_input))
    return sum(numbers)


def part_b(puzzle_input):
    return recurse_items(json.loads(puzzle_input))


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(*sys.argv[1:])
