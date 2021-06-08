import re
import sys
from typing import Tuple, Dict
import itertools
import sympy


BUDGET = 100

IngredientValues = Dict[str, int]


def parse(line: str) -> Tuple[str, IngredientValues]:
    pattern = re.compile(r'(\w+) (-?\d+)')
    name, raw_components = line.split(':')
    return name, {k: int(v) for k, v in re.findall(pattern, raw_components)}


def score_recipe(ingredients: Dict[str, IngredientValues], allocations: Dict[str, int]):
    assert sum(allocations.values()) == BUDGET

    score = 1
    for attribute in filter(lambda x: x != "calories", next(iter(ingredients.values())).keys()):
        score *= sum(ingredients[name][attribute] * allocations[name] for name in allocations.keys())
        if score <= 0:
            return 0

    return score


def brute_force_max(ingredients):
    """Just brute force it and rely on the score early stopping to help speed up. Will refactor to a Lagrangian multiplier
    when I have time"""

    alloc_vectors = filter(lambda x: sum(x) == 100, itertools.product(range(BUDGET + 1), repeat=len(ingredients)))
    return max(score_recipe(ingredients, dict(zip(ingredients.keys(), alloc))) for alloc in alloc_vectors)


def compile_lagrange_multiplier(ingredients):
    xs = sympy.symbols('x:{}'.format(len(ingredients)))

    # Going to skip the negative logic for the moment
    objective = ingredients



def main():
    with open(sys.argv[1], 'r') as f:
        ingredients = dict(parse(line) for line in f)

    print(brute_force_max(ingredients))


if __name__ == "__main__":
    main()
