import fileinput
from collections import namedtuple
import re
from typing import List


Instruction = namedtuple('Instruction', ['amt', 'fr', 'to'])
Stack = List  # Lists are great for LIFO, not committing in case we need to change to deque later


def parse_instruction(line) -> Instruction:
    rxp = re.compile(r'move ([0-9]+) from ([0-9]+) to ([0-9]+)')
    return Instruction(*map(int, rxp.match(line.strip()).groups()))


def build_stacks(input) -> List[Stack]:
    # Scan for number of stacks
    # Store stacklines for bottom up construction while we're at it, since can't rewind STDIN reliably
    stacklines = []
    for line in input:
        tokens = line.strip().split()
        if all(token.isnumeric() for token in tokens):
            stacks = [[] for _ in range(int(tokens[-1]))]
            break
        else:
            stacklines.append(line)

    while stacklines:  # Now pop off to build from the bottom!
        for idx, cargo in enumerate(stacklines.pop().strip()):
            if cargo.isalpha():
                stacks[idx // 4].append(cargo)

    return stacks


def execute_instruction(stacks: List[Stack], inst: Instruction) -> None:  # Mutates stacks, no return
    pass


def main():
    with fileinput.input() as input:
        stacks = build_stacks(input)


if __name__ == "__main__":
    main()
