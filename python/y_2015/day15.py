import re
import sys
from typing import Tuple, Dict
import itertools
import sympy as sp


BUDGET = 100

IngredientValues = Dict[str, int]


def parse(line: str) -> Tuple[str, IngredientValues]:
    pattern = re.compile(r'(\w+) (-?\d+)')
    name, raw_components = line.split(':')
    return name, {k: int(v) for k, v in re.findall(pattern, raw_components)}


def lagrange_multiplier(ingredients):
    """Sympy is kinda slow so this isn't actually a particulatly fast solution, but it's just cool to show that there's
    an (almost) analytic solution available."""
    xs = sp.symbols('x:{}'.format(len(ingredients)))
    lmb = sp.symbols('lmb')

    # SKip negative logic due to differentiability requirements
    objective = 1
    for attribute in filter(lambda x: x != "calories", next(iter(ingredients.values())).keys()):
        objective *= sum(list(ingredients.values())[i][attribute] * x for i, x in enumerate(xs))

    constraint = sum(xs) - BUDGET

    L = objective - lmb * constraint
    grad_L = [sp.diff(L, wrt) for wrt in (*xs, lmb)]  # Vector calc time
    candidates = sp.solve(grad_L, (*xs, lmb), dict=True)  # Stationary points of L

    # Find the optimal stationary point
    optimal_float = max(candidates, key=lambda assignment: objective.subs(assignment))
    return optimal_float


def main():
    with open(sys.argv[1], 'r') as f:
        ingredients = dict(parse(line) for line in f)

    print(lagrange_multiplier(ingredients))


if __name__ == "__main__":
    main()
