import fileinput
from typing import Iterable


def priority(item: str) -> int:
    if ord(item) >= ord('a'):
        return ord(item) - ord('a') + 1
    else:
        return ord(item) - ord('A') + 27


def find_duplicate(backpack: str) -> str:
    halfway = len(backpack) // 2
    return find_common_element((backpack[:halfway], backpack[halfway:]))


def slicer(xs, slice_length):
    return (xs[i:i+slice_length] for i in range(0, len(xs), slice_length))


def find_common_element(containers: Iterable[str]) -> str:
    return set.intersection(*(set(c) for c in containers)).pop()  # Neat little one-liner


def main():
    backpacks = [line.strip() for line in fileinput.input()]
    print(sum(priority(find_duplicate(b)) for b in backpacks))
    print(sum(priority(find_common_element(bs)) for bs in slicer(backpacks, 3)))


if __name__ == "__main__":
    main()
