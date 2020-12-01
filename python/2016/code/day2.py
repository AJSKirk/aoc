import sys
import termcolor_util as tc


class Agent:
    def __init__(self, keypad, row, col):
        self.row = row
        self.col = col
        self.keypad = keypad
        self.keypad_max = len(keypad) - 1
        self.command_dict = {'U': self.up, 'D': self.down, 'L': self.left, 'R': self.right}

    def up(self):
        self.row = max(0, self.row - 1)

    def down(self):
        self.row = min(self.keypad_max, self.row + 1)

    def left(self):
        self.col = max(0, self.col - 1)

    def right(self):
        self.col = min(self.keypad_max, self.col + 1)

    def move(self, command):
        prev = (self.row, self.col)
        self.command_dict[command]()
        if self.key == '.':
            self.row, self.col = prev

    @property
    def key(self):
        return self.keypad[self.row][self.col]


def load_input(fname):
    with open(fname, 'r') as f:
        return f.readlines()


def execute(puzzle_input, keypad, start_row, start_col):
    agent = Agent(keypad, start_row, start_col)
    code = []
    for instruction in puzzle_input:
        for move in instruction.strip():
            agent.move(move)
        code.append(agent.key)

    return ''.join(str(i) for i in code)


def part_a(puzzle_input):
    keypad = ((1, 2, 3), (4, 5, 6), (7, 8, 9))
    return execute(puzzle_input, keypad, 1, 1)


def part_b(puzzle_input):
    keypad = ('..1..', '.234.', '56789', '.ABC.', '..D..')
    return execute(puzzle_input, keypad, 2, 0)


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
