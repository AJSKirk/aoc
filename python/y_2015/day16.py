import sys
import re
from typing import Dict, Tuple
from operator import eq, gt, lt
from collections import namedtuple


Sue = Dict[str, int]
ReportClause = namedtuple('ReportClause', ('op', 'val'))


MFCSAM_REPORT = {
    'children': ReportClause(eq, 3),
    'cats': ReportClause(gt, 7),
    'samoyeds': ReportClause(eq, 2),
    'pomeranians': ReportClause(lt, 3),
    'akitas': ReportClause(eq, 0),
    'vizslas': ReportClause(eq, 0),
    'goldfish': ReportClause(lt, 5),
    'trees': ReportClause(gt, 3),
    'cars': ReportClause(eq, 2),
    'perfumes': ReportClause(eq, 1)
}


def parse(line: str) -> Tuple[int, Sue]:
    pattern = r'(\w+): (\d+)'
    suenum = re.findall('\d+', line)[0]
    return suenum, {k: int(v) for k, v in re.findall(pattern, line)}


def validate_sue(sue: Sue, old_retroencabulator_mode: bool, report=MFCSAM_REPORT) -> bool:
    return all((report[key].op if old_retroencabulator_mode else eq)(sue[key], report[key].val) for key in sue)


def main():
    with open(sys.argv[1], 'r') as f:
        sues = dict(parse(line) for line in f)

    print('The Correct Sue ID is: {}'.format(next(suenum for suenum, sue in sues.items() if validate_sue(sue, False))))
    print('The Real Correct Sue ID is: {}'.format(next(suenum for suenum, sue in sues.items() if validate_sue(sue, True))))


if __name__ == '__main__':
    main()
