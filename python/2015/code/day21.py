import sys
import termcolor_util as tc
from collections import namedtuple
import itertools
from copy import copy

ATTRS_LIST = ['damage', 'armour']
Item = namedtuple('Item', ['cost'] + ATTRS_LIST)


class Fighter:
    def __init__(self, hp, damage, armour):
        self.hp = hp
        self.damage = damage
        self.armour = armour

    def hit(self, target):
        target.hp -= max(1, self.damage - target.armour)
        return target.hp <= 0


def generate_loadouts():
    weapons = [Item(8, 4, 0), Item(10, 5, 0), Item(25, 6, 0), Item(40, 7, 0), Item(74, 8, 0)]
    armours = [Item(0, 0, 0), Item(13, 0, 1), Item(31, 0, 2), Item(53, 0, 3), Item(75, 0, 4), Item(102, 0, 5)]
    rings = [Item(0, 0, 0), Item(0, 0, 0), Item(25, 1, 0), Item(50, 2, 0), Item(100, 3, 0),
             Item(20, 0, 1), Item(40, 0, 2), Item(80, 0, 3)]

    for combo in itertools.product(weapons, armours, rings, rings):
        if combo[2] != combo[3]:  # Can't wear same ring twice
            yield Item(*[sum(item._asdict()[attr] for item in combo) for attr in ['cost'] + ATTRS_LIST])


def try_fight(loadout, enemy):
    you = Fighter(100, loadout.damage, loadout.armour)
    while True:
        if you.hit(enemy): return True
        if enemy.hit(you): return False


def brute_force(enemy, fair=True):
    for loadout in generate_loadouts():
        if try_fight(loadout, copy(enemy)) == fair:
            yield loadout.cost


def load_input(fname):
    attrs = {}
    with open(fname, 'r') as f:
        for attr_name in ['hp'] + ATTRS_LIST:
            attrs[attr_name] = int(f.readline().strip().split(': ')[1])

    return Fighter(**attrs)


def part_a(puzzle_input):
    return min(cost for cost in brute_force(puzzle_input))


def part_b(puzzle_input):
    return max(cost for cost in brute_force(puzzle_input, fair=False))


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
