import sys
import re
from typing import Dict, Tuple


Sue = Dict[str, int]


MFCSAM_REPORT = {
    'children': 3,
    'cats': 7,
    'samoyeds': 2,
    'pomeranians': 3,
    'akitas': 0,
    'vizslas': 0,
    'goldfish': 5,
    'trees': 3,
    'cars': 2,
    'perfumes': 1
}


def parse(line: str) -> Tuple[int, Sue]:
    pattern = r'(\w+): (\d+)'
    suenum = re.findall('\d+', line)[0]
    return suenum, {k: int(v) for k, v in re.findall(pattern, line)}


def validate_sue(sue: Sue, report=MFCSAM_REPORT) -> bool:
    return all(sue.get(key, rep_value) == rep_value for key, rep_value in report.items())


def main():
    with open(sys.argv[1], 'r') as f:
        sues = dict(parse(line) for line in f)

    print('The Correct Sue ID is: {}'.format(next(suenum for suenum, sue in sues.items() if validate_sue(sue))))


if __name__ == '__main__':
    main()
