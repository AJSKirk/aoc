import sys
import termcolor_util as tc
import hashlib
import itertools


def part_both(secret_key, n_lead_zeroes=5):
    for attempt in itertools.count(1):
        m = hashlib.new('md5')
        m.update(bytes(secret_key + str(attempt), 'utf-8'))
        if m.hexdigest()[:n_lead_zeroes] == '0' * n_lead_zeroes:
            return attempt


def main(secret_key):
    print(f'The Answer to Part A is: {tc.green(part_both(secret_key, 5))}')
    print(f'The Answer to Part B is: {tc.green(part_both(secret_key, 6))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [key]')
    else:
        main(sys.argv[1])
