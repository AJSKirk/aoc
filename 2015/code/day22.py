import sys
import termcolor_util as tc
from collections import namedtuple
import itertools
from copy import copy

ATTRS_LIST = ['damage', 'armour']
Item = namedtuple('Item', ['cost'] + ATTRS_LIST)

spells

def branch(player, enemy):


class Fighter:
    def __init__(self, hp, damage, armour):
        self.hp = hp
        self.damage = damage
        self.armour = armour

    def hit(self, target):
        target.hp -= max(1, self.damage - target.armour)
        return target.hp <= 0


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
