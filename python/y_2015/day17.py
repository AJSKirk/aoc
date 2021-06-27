import sys
from typing import Iterable


TOTAL_VOL = 150


def possible_combos(to_store: int, bins: Iterable[int]):
    """Recursive - Relies on the fact that no bins have negative volume"""
    if to_store < 0 or to_store > sum(bins):  # Early-pruning
        return 0
    if to_store == 0:
        return 1
    return possible_combos(to_store, bins[1:]) + possible_combos(to_store - bins[0], bins[1:])


def main():
    with open(sys.argv[1], 'r') as f:
        bins = sorted([int(line.strip()) for line in f], reverse=True)

    print("Possible Combinations: {}".format(possible_combos(TOTAL_VOL, bins)))


if __name__ == '__main__':
    main()
