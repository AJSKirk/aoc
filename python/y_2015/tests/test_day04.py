from y_2015.day04 import *


def test_compute_hash():
    assert compute_hash('abcdef', 609043).startswith('000001dbbfa')
    assert compute_hash('pqrstuv', 1048970).startswith('000006136ef')


def test_crack_hash():
    assert crack_hash('abcdef', 5) == 609043
    assert crack_hash('pqrstuv', 5) == 1048970
