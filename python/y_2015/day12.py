import sys
import re
import operator
from functools import reduce
import math

EXTRACT_REGEXP = r'(\[)|(\])|(\{)|(\})|(-*\d+)|(red)'


def neg_safe_cast(token):
    """Needed because an .isnumeric() check fails to pick up negatives"""
    try:
        return int(token)
    except ValueError:
        return 0


def total_numerics(tokens):
    return reduce(operator.add, map(neg_safe_cast, tokens))


def no_red_sum(tokens):
    """Using import json is cheating, let's parse it ourselves in a sinlge pass. Hope you like stacks."""
    sums = [0]
    stack = []
    is_red = False

    for token in tokens:
        if token == 'red' and not is_red and stack[-1] == '{':
            is_red = True
            sums[-1] = 0
            stack.append('red')
        elif token == '{':
            sums.append(0)
            stack.append('{')
        elif token == '}':
            last_sum = sums.pop()
            sums[-1] += last_sum
            if stack[-1] == 'red':
                stack.pop()
                is_red = False
            stack.pop()
        elif token == '[':
            stack.append('[')
            sums.append(0)
        elif token == ']':
            stack.pop()
            last_sum = sums.pop()
            sums[-1] += last_sum
        elif not is_red:
            sums[-1] += neg_safe_cast(token)

    assert len(sums) == 1
    return sums.pop()


def get_tokens(raw_json):
    return map(lambda m: m.group(), re.finditer(EXTRACT_REGEXP, raw_json))


def main():
    with open(sys.argv[1], 'r') as f:
        tokens = get_tokens(f.read().strip())

    #print(total_numerics(tokens))
    print(no_red_sum(tokens))


if __name__ == "__main__":
    main()
