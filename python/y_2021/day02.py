import sys
from functools import reduce
from typing import Iterable
import operator as op
from collections import namedtuple

STEPWISE_MULTIPLIERS = {"forward": (1, 0), "down": (0, 1), "up": (0, -1)}

State = namedtuple("State", ["distance", "aim", "depth"])


def parse(instructions):
    instructions = [line.strip().split() for line in instructions]
    scalar_vec_tuples = ((STEPWISE_MULTIPLIERS[instruction], int(magnitude)) for instruction, magnitude in instructions)
    move_tuples = ([dim * mag for dim in dim_tuple] for dim_tuple, mag in scalar_vec_tuples)

    return move_tuples


def angular_increment(state, moves):
    forward_move, aim_move = moves

    return State(state.distance + forward_move, state.aim + aim_move, state.depth + state.aim * forward_move)


def main():
    moves = list(parse(sys.stdin))

    print(f"Final Stepwise Depth * Distance: {reduce(op.mul, (sum(dim) for dim in zip(*moves)))}")
    final_state = reduce(angular_increment, moves, State(0, 0, 0))
    print(f"Final Angular Depth * Distance: {final_state.distance * final_state.depth}")


if __name__ == "__main__":
    main()
