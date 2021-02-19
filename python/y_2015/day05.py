import re
import sys
from typing import Tuple, Iterable


Syndrome = Iterable[bool]

TEST_SETS = ((r"(.*[aeiou]){3}",        # Three vowels with anything in between
              r".*(.)\1",               # Repeated letter
              r"(?!.*(ab|cd|pq|xy))"),  # No naughty pairs anywhere

             (r".*(.{2}).*\1",          # Repeated pair
              r".*(.).\1"))             # Repeated letter with single char in middle


def is_nice(candidate: str, tests: Tuple[str, ...]) -> Syndrome:
    return (re.match(test, candidate) is not None for test in tests)


def main():
    with open(sys.argv[1], "r") as f:
        for test_set in TEST_SETS:
            f.seek(0)
            print("Nice strings: {}".format(sum(all(is_nice(cand, test_set)) for cand in f)))


if __name__ == "__main__":
    main()
