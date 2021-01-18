import sys
from collections import Counter
from itertools import accumulate


INSTRUCTION_MAP = {'^': (0, 1), '<': (-1, 0), 'v': (0, -1), '>': (1, 0)}


def count_houses(instructions: str, num_santas: int = 1) -> int:
    update = lambda loc, delta: tuple(sum(pair) for pair in zip(loc, delta))  # Works on n dimensions
    houses = Counter(((0, 0),))
    for start in range(num_santas):  # Inverting this loop might get better cache performance but real small difference
        houses.update(accumulate((INSTRUCTION_MAP[i] for i in instructions[start::num_santas]), update))
    return len(houses)


def main():
    with open(sys.argv[1], 'r') as f:
        instructions = f.read().strip()

    print("Number of distinct houses visited by Santa: {}".format(count_houses(instructions)))
    print("Number of distinct houses visited by Santa and Robo-Santa: {}".format(count_houses(instructions, 2)))


if __name__ == "__main__":
    main()
