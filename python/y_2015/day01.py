from functools import reduce
from operator import add
from itertools import accumulate
import sys
from typing import Generator

INSTRUCTION_MAP = {'(': 1, ')': -1}


def translate(instructions: str) -> Generator[int, None, None]:
    return (INSTRUCTION_MAP[i] for i in instructions)


def final_floor(instructions: str) -> int:
    steps = translate(instructions)
    return reduce(add, steps, 0)


def first_negative(instructions: str) -> int:
    steps = translate(instructions)
    return next(i for i, floor in enumerate(accumulate(steps, add), 1) if floor < 0)


def main():
    with open(sys.argv[1], 'r') as f:
        instructions = f.read().strip()
    print("The final floor is: {}".format(final_floor(instructions)))
    print("The first basement is on step: {}".format(first_negative(instructions)))


if __name__ == "__main__":
    main()
