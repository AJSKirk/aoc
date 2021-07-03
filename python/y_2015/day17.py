import sys
from typing import List


TOTAL_VOL = 150


def possible_combos(to_store: int, bins: List[int], used_so_far: int = 0):
    """Recursive - Relies on the fact that no bins have negative volume"""
    if to_store == 0:
        yield used_so_far
        return
    if to_store < 0 or to_store > sum(bins):  # Early-pruning
        return
    yield from possible_combos(to_store, bins[1:], used_so_far)
    yield from possible_combos(to_store - bins[0], bins[1:], used_so_far + 1)


def main():
    with open(sys.argv[1], 'r') as f:
        bins = sorted([int(line.strip()) for line in f], reverse=True)  # Sorting largest-first maximises pruning

    possible_bin_counts = list(possible_combos(TOTAL_VOL, bins))
    print("Possible Combinations:   {:>4}".format(len(possible_bin_counts)))
    print("Different Smallest Ways: {:>4}".format(sum(1 for i in possible_bin_counts if i == min(possible_bin_counts))))


if __name__ == '__main__':
    main()
