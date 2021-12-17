import sys
from itertools import takewhile, accumulate


class Board:
    def __init__(self, lines):
        self.board = [[int(cell) for cell in line.strip().split()] for line in lines]

    @property
    def board_transposed(self):
        return zip(*self.board)

    def is_winner(self, seen_numbers):
        if any(map(lambda board: any(all(cell in seen_numbers for cell in row) for row in board),
                       (self.board, self.board_transposed))):
            return self.score(seen_numbers)
        else:
            return 0

    def score(self, seen_numbers):
        unmarked = sum(sum(cell for cell in row if cell not in seen_numbers) for row in self.board)
        return unmarked * seen_numbers[-1]


def chunkerator(instructions):
    while True:
        chunk = list(takewhile(lambda row: row.strip() != '', instructions))
        if chunk:
            yield chunk
        else:
            return


def play_bingo(numbers, boards):
    seen_numbers = accumulate(numbers, lambda state, new: state + [new], initial=[])
    return (max(b.is_winner(ns) for b in boards) for ns in seen_numbers)


def parse(instructions):
    numbers = [int(n) for n in instructions.readline().strip().split(',')]
    instructions.readline()
    boards = list(Board(chunk) for chunk in chunkerator(instructions))

    return numbers, boards


def main():
    numbers, boards = parse(sys.stdin)

    print(f"Score of the first Complete Board: {next(s for s in play_bingo(numbers, boards) if s != 0)}")


if __name__ == "__main__":
    main()
