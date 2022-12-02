import fileinput
from enum import Enum
from typing import Dict
from itertools import cycle

PLAYS = Enum('PLAYS', ['ROCK', 'PAPER', 'SCISSORS'])


def main():
    games = [tuple(line.strip().split()) for line in fileinput.input()]
    op_translator = dict(zip("ABC", PLAYS))
    first_translator = dict(zip("XYZ", PLAYS))

    print(f"With Naive Strat: {sum(score_game(op_translator[op], first_translator[my]) for (op, my) in games)}")
    print(f"Advanced Strat {sum(score_game(op_translator[op], strategy_calculator(op_translator[op], my)) for (op, my) in games)}")


def strategy_calculator(opponents_hand, my_instruction):
    strat = {'X': PLAYS(3 if (v := opponents_hand.value - 1) == 0 else v),  # Walrus time!
             'Y': opponents_hand,
             'Z': PLAYS(opponents_hand.value % len(PLAYS) + 1)}
    return strat[my_instruction]


def score_game(opponents_hand: PLAYS, my_hand: PLAYS):
    if my_hand == opponents_hand:
        return my_hand.value + 3
    elif my_hand.value == (opponents_hand.value % len(PLAYS)) + 1:  # Exploit circular relationship
        return my_hand.value + 6
    else:
        return my_hand.value


if __name__ == "__main__":
    main()
