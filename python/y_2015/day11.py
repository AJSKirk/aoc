import sys
import re
from typing import List


def is_valid(cand: str) -> bool:
    has_repeats = re.match(r'.*((.)\2.*){2}', cand)
    no_invalids = not re.match(r'.*[iol]', cand)

    if not all((has_repeats, no_invalids)):
        return False

    values = list(map(ord, cand))
    ascend_strs = zip(*(values[i:] for i in range(3)))
    for ascend_str in ascend_strs:
        pairs = zip(*(ascend_str[i:] for i in range(2)))
        if all(l + 1 == r for l, r in pairs):
            return True

    return False


def increment(password: List[str], pos=-1) -> List[str]:
    if password[pos] == 'z':
        password[pos] = 'a'
        return increment(password, pos - 1)

    password[pos] = chr(ord(password[pos]) + 1)
    return password if password[pos] not in 'iol' else increment(password, pos)


def incrementer(start: str):
    start_l = list(start)
    while True:
        yield ''.join(increment(start_l))


def main():
    with open(sys.argv[1], 'r') as f:
        start = f.read().strip()

    for i, pwd in zip(range(2), filter(is_valid, incrementer(start))):
        print("Password {}: {}".format(i, pwd))


if __name__ == "__main__":
    main()
