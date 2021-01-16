from y_2015.day02 import *


def test_box_parser():
    assert box_parser("1x3x2\n") == (1,2,3)


def test_paper_required():
    assert paper_required((2, 3, 4)) == 58
    assert paper_required((1, 1, 10)) == 43


def test_ribbon_required():
    assert ribbon_required((2, 3, 4)) == 34
    assert ribbon_required((1, 1, 10)) == 14
