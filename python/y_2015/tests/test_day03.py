from y_2015.day03 import *


def test_count_houses():
    assert count_houses(">") == 2
    assert count_houses("^>v<") == 4
    assert count_houses("^v^v^v^v^v") == 2


def test_robo_santa():
    assert count_houses("^v", 2) == 3
    assert count_houses("^>v<", 2) == 3
    assert count_houses("^v^v^v^v^v", 2) == 11
