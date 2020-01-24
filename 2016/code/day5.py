import sys
import termcolor_util as tc
import hashlib
import itertools


def code_generator(secret_key, n_lead_zeroes=5):
    for attempt in itertools.count(1):
        m = hashlib.new('md5')
        m.update(bytes(secret_key + str(attempt), 'utf-8'))
        if m.hexdigest()[:n_lead_zeroes] == '0' * n_lead_zeroes:
            yield m.hexdigest()[n_lead_zeroes], m.hexdigest()[n_lead_zeroes + 1]


def part_a(puzzle_input, code_length=8):
    return ''.join(itertools.islice((a for a, b in code_generator(puzzle_input)), code_length))


def part_b(puzzle_input, code_length=8):
    out = ['-'] * code_length
    generator = code_generator(puzzle_input)
    while '-' in out:
        pos, val = next(generator)
        if pos.isdigit() and int(pos) < code_length and out[int(pos)] == '-':
            out[int(pos)] = val
            print(tc.red(''.join(out)))

    return ''.join(out)


def main(puzzle_input):
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
