import fileinput
from collections import namedtuple
import re
from typing import List
from copy import deepcopy


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


def execute_instruction(stacks: List[Stack], inst: Instruction, cranemodel=9000) -> None:  # Mutates stacks, no return
    assert cranemodel in (9000, 9001)
    if cranemodel == 9000:
        for _ in range(inst.amt):
            stacks[inst.to - 1].append(stacks[inst.fr - 1].pop())
    else:
        stacks[inst.to - 1].extend(stacks[inst.fr - 1][-inst.amt:])  # Extend, not append!
        del stacks[inst.fr - 1][-inst.amt:]


def main():
    with fileinput.input() as input:
        stacks = build_stacks(input)
        multistacks = [deepcopy(stacks) for _ in range(2)]  # Copy and simulate in parallel
        input.readline()  # Clear blank line
        for line in input:
            instruction = parse_instruction(line.strip())
            execute_instruction(multistacks[0], instruction)
            execute_instruction(multistacks[1], instruction, cranemodel=9001)

    for idx, stacks in enumerate(multistacks):
        print(f"Simulation {idx + 1}: {''.join(s[-1] for s in stacks)}")  # Print top crates


if __name__ == "__main__":
    main()
