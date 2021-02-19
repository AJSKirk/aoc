import re
import sys
from typing import Tuple


TEST_SETS = ((r"(.*[aeiou]){3}",  # Three vowels with anything in between
              r".*(.)\1",  # Repeated letter
              r"(?!.*(ab|cd|pq|xy))"),  # No naughty pairs anywhere

             (r".*(..).*\1",
              r".*(.).\1"))


def is_nice(candidate: str, tests: Tuple[str, ...]) -> bool:
    return all(re.match(test, candidate) is not None for test in tests)


def main():
    with open(sys.argv[1], "r") as f:
        for test_set in TEST_SETS:
            f.seek(0)
            print("Nice strings: {}".format(sum(1 for cand in f if is_nice(cand, test_set))))


if __name__ == "__main__":
    main()
