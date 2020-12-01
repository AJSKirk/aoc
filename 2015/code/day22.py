import sys
import termcolor_util as tc
from collections import namedtuple
import itertools
from copy import copy

ATTRS_LIST = ['damage', 'armour']
Item = namedtuple('Item', ['cost'] + ATTRS_LIST)


class Player:
    def __init__(self, hp, damage=0, mana=0):
        self.hp = hp
        self.damage = damage
        self.armour = 0
        self.mana = mana

    def hit(self, target):
        target.hp -= max(1, self.damage - target.armour)
        return target.hp <= 0

    def magic_missile(self, target):
        self.mana -= 53
        target.hp -= 4
        return target.hp <= 0

    def drain(self, target):
        self.hp += 2
        target.hp -= 2
        return target.hp <= 0


def fight(you, enemy, counters, spent):
    def run_counters():
        if counters['poison']:
            counters['poison'] -= 1
            enemy.hp -= 3

        if counters['shield']:
            counters['shield'] -= 1
            you.armour = 7
        else:
            you.armour = 0

        if counters['recharge']:
            counters['recharge'] -= 5
            you.mana += 101

        return enemy.hp <= 0

    if run_counters(): return spent # Mana spend
    ## Player's turn
    if run_counters(): return spent # Mana spend
    ## Boss's turn


def try_fight(loadout, enemy):
    you = Player(50, mana=500)
    poison_counter =
    while True:
        if you.hit(enemy): return True
        if enemy.hit(you): return False


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
