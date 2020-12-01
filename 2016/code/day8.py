import sys
import termcolor_util as tc


def load_input(fname):
    with open(fname, 'r') as f:
        return f.readlines()


class Screen:
    def __init__(self, width=50, height=6):
        self.width = width
        self.height = height
        self.grid = []
        for row in range(height):
            self.grid.append([False] * width)  # Solve annoying copy issue

    def rect(self, a, b):
        for col in range(a):
            for row in range(b):
                self.grid[row][col] = True

    def rotate(self, mode, idx, by):
        if mode == 'row':
            row = self.grid[idx]
            for _ in range(by):
                row.insert(0, row.pop())  # Make this a deque if slow
        elif mode == 'column':
            copy_col = []
            for row_idx in range(self.height):
                copy_col.append(self.grid[row_idx][idx])

            for row_idx in range(self.height):
                self.grid[row_idx][idx] = copy_col[row_idx - by]
        else:
            raise ValueError('Rotate mode must be either "row" or "column"')

    def runcom(self, command_string):
        components = command_string.strip().split(' ')
        if components[0] == 'rect':
            a, b = (int(i) for i in components[1].split('x'))
            self.rect(a, b)
        elif components[0] == 'rotate':
            mode = components[1]
            idx = int(components[2].split('=')[-1])
            by = int(components[-1])
            self.rotate(mode, idx, by)
        else:
            raise ValueError('Improper command')

    @property
    def total_on(self):
        return sum(sum(row) for row in self.grid)

    def show(self):
        for row in self.grid:
            for col in row:
                if col:
                    print('*', end='')
                else:
                    print(' ', end='')
            print('')


def part_a(puzzle_input):
    screen = Screen()
    for command in puzzle_input:
        screen.runcom(command)

    return screen.total_on


def part_b(puzzle_input):
    screen = Screen()
    for command in puzzle_input:
        screen.runcom(command)
    screen.show()


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
