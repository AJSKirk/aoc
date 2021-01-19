from y_2015.day03 import *


def test_count_houses():
    assert count_houses([INSTRUCTION_MAP[i] for i in ">"]) == 2
    assert count_houses([INSTRUCTION_MAP[i] for i in "^>v<"]) == 4
    assert count_houses([INSTRUCTION_MAP[i] for i in "^v^v^v^v^v"]) == 2


def test_robo_santa():
    assert count_houses([INSTRUCTION_MAP[i] for i in "^v"], 2) == 3
    assert count_houses([INSTRUCTION_MAP[i] for i in "^>v<"], 2) == 3
    assert count_houses([INSTRUCTION_MAP[i] for i in "^v^v^v^v^v"], 2) == 11
