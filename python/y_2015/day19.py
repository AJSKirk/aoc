import sys
from collections import namedtuple
import re
from typing import List, IO


Rule = namedtuple('Rule', ['fr', 'to'])


def parse_file(file: IO) -> (List[Rule], str):
    rules = []
    for line in file:
        if '=>' in line:
            rules.append(Rule(*line.strip().split(" => ")))
        elif line.strip() == '':
            continue
        else:
            return rules, line.strip()


def possible_transforms(rules, origin):
    for rule in rules:
        for match in re.finditer(rule.fr, origin):
            yield "{}{}{}".format(origin[:match.start()], rule.to, origin[match.end():])


def main():
    with open(sys.argv[1], 'r') as f:
        rules, medicine = parse_file(f)

    print("Possible Transforms: {}".format(len(set(possible_transforms(rules, medicine)))))


if __name__ == "__main__":
    main()
