import sys
import termcolor_util as tc
from operator import mul
from functools import reduce
import itertools


def load_input(fname):
    ingredients = {}
    with open(fname, 'r') as f:
        for line in f.readlines():
            name, props = line.strip().split(': ')
            metrics = [prop.split(' ')[0] for prop in props.split(', ')]
            props = [int(prop.split(' ')[1]) for prop in props.split(', ')]
            ingredients[name] = dict(zip(metrics, props))
    return ingredients, metrics


def score_recipe(recipe, ingredients, metrics):
    values = [max(0, sum(ingredients[name][value] * recipe[name] for name in ingredients)) for value in metrics]
    return reduce(mul, values)


def brute_force(ingredients, metrics, total_qty=100):
    names = ingredients.keys()
    for qtys in itertools.product(range(total_qty + 1), repeat=len(names)):
        if sum(qtys) == 100:
            recipe = dict(zip(names, qtys))
            yield recipe, score_recipe(recipe, ingredients, metrics)


def part_a(ingredients, metrics):
    metrics.remove('calories')
    return max(brute_force(ingredients, metrics), key=lambda pair: pair[1])


def part_b(puzzle_input, metrics):
    pass


def main(fname):
    puzzle_input, metrics = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input, metrics))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input, metrics))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
