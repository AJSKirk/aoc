import re
import sys


def is_nice(candidate: str) -> bool:
    tests = (r"(.*[aeiou]){3}",  # Three vowels with anything in between
             r".*(.)\1",  # Repeated letter
             r"(?!.*(ab|cd|pq|xy))")  # No naughty pairs anywhere
    return all(re.match(test, candidate) is not None for test in tests)


def main():
    with open(sys.argv[1], "r") as f:
        print("Nice strings: {}".format(sum(1 for cand in f if is_nice(cand))))


if __name__ == "__main__":
    main()
