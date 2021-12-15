import sys
from typing import Generator, Iterable

INSTRUCTION_MAP = {'(': 1, ')': -1}


def depth_increases(depths: Iterable[int]) -> int:
    return sum(y > x for x, y in zip(depths[:-1], depths[1:]))


def window_increases(depths: Iterable[int]) -> int:
    windows = [sum(window) for window in zip(*(depths[n:] for n in range(3)))]
    return sum(y > x for x, y in zip(windows[:-1], windows[1:]))


def main():
    depths = [int(line.strip()) for line in sys.stdin]
    print("Number of Dives: {}".format(depth_increases(depths)))
    print("Number of Rolling Window Dives: {}".format(window_increases(depths)))


if __name__ == "__main__":
    main()
