import sys
import re


def excess_representation(s: str) -> int:
    return len(s) - len(re.findall(r'([a-z]|\\\\|\\"|\\x[0-9a-f]{2})', s))


def required_additions(s: str) -> int:
    return len(re.findall(r'("|\\)', s)) + 2  # Just add enclosing quotes and an extra slash for each slash or quote


def main():
    with open(sys.argv[1], 'r') as f:
        print(sum(excess_representation(line.strip()) for line in f))
        f.seek(0)
        print(sum(required_additions(line.strip()) for line in f))


if __name__ == "__main__":
    main()
