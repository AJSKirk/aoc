from y_2015.day01 import *


def test_translate():
    assert list(translate("(())")) == [1, 1, -1, -1]


def test_final_floor():
    assert final_floor("(())") == 0
    assert final_floor("()()") == 0
    assert final_floor("(((") == 3
    assert final_floor(")())())") == -3


def test_first_negative():
    assert first_negative("()())") == 5
