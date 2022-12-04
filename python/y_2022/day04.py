import fileinput
from typing import Tuple
from collections import namedtuple


Elf = namedtuple("Elf", ["fr", "to"])
Pair: Tuple[Elf, Elf]


def parse_line(line: str):
    elves = line.strip().split(',')
    return tuple(Elf(*(int(i) for i in elf.split('-'))) for elf in elves)


def check_overlaps(pair, partial=False) -> bool:
    # over = candidate overlapping set, under = candidate overlapped set
    for idx, over in enumerate(pair):
        under = pair[(idx + 1) % len(pair)]
        if over.fr <= under.fr and over.to >= under.to:
            return True
        # Check partial overlaps - only need to check one direction as the other will be checked on the next loop iter
        if partial and (over.fr <= under.fr) and (over.to >= under.fr):
            return True

    return False


def main():
    pairs = [parse_line(line) for line in fileinput.input()]
    print(sum(check_overlaps(pair) for pair in pairs))
    print(sum(check_overlaps(pair, True) for pair in pairs))


if __name__ == "__main__":
    main()