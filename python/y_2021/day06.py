import sys
from collections import Counter, defaultdict
from typing import Dict
from functools import reduce


WAIT_PERIOD = 6
FIRST_DELAY = 2

State = Dict[int, int]


def step(state: State) -> State:
    new_state = dict()
    new_state[WAIT_PERIOD] = new_state[WAIT_PERIOD + FIRST_DELAY] = state.get(0, 0)  # Births

    for time in range(WAIT_PERIOD + FIRST_DELAY):
        new_state[time] = new_state.get(time, 0) + state.get(time + 1, 0)

    return new_state


def main():
    state = Counter(map(int, sys.stdin.read().strip().split(',')))

    for n_steps in (80, 256):
        print(f"Lanternfish after {n_steps}: {sum(reduce(lambda s, _: step(s), range(n_steps), state).values())}")


if __name__ == "__main__":
    main()
