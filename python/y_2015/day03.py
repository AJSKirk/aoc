import sys
from itertools import accumulate
from typing import List, Tuple

Step = Tuple[int, ...]
Sequence = List[Step]
INSTRUCTION_MAP = {'^': (0, 1), '<': (-1, 0), 'v': (0, -1), '>': (1, 0)}


def count_houses(instructions: Sequence, num_santas: int = 1) -> int:
    def update(loc, delta): return tuple(sum(pair) for pair in zip(loc, delta))  # Works on n dimensions
    houses = {(0, 0)}
    for start in range(num_santas):  # Inverting this loop might get better cache performance but real small difference
        houses |= set(accumulate(instructions[start::num_santas], update))
    return len(houses)


def main():
    with open(sys.argv[1], 'r') as f:
        instructions = [INSTRUCTION_MAP[i] for i in f.read().strip()]

    print("Number of distinct houses visited by Santa: {}".format(count_houses(instructions)))
    print("Number of distinct houses visited by Santa and Robo-Santa: {}".format(count_houses(instructions, 2)))


if __name__ == "__main__":
    main()
