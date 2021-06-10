import re
import sys
from typing import Tuple, Dict, List
import itertools
import sympy as sp


BUDGET = 100
CALORIE_BUDGET = 500

IngredientValues = Dict[str, int]


def parse(line: str) -> Tuple[str, IngredientValues]:
    pattern = re.compile(r'(\w+) (-?\d+)')
    name, raw_components = line.split(':')
    return name, {k: int(v) for k, v in re.findall(pattern, raw_components)}


def symbolic_objective(ingredients) -> Tuple[List[sp.Symbol], sp.Eq]:
    """Compile the Sympy objective function. Return list of vars and function."""
    assignments = sp.symbols(' '.join(ingredients.keys()))

    # Skip negative logic due to differentiability requirements
    objective = 1
    for attribute in filter(lambda x: x != "calories", next(iter(ingredients.values())).keys()):
        objective *= sum(ingredients[str(x)][attribute] * x for x in assignments)

    return assignments, objective


def lagrange_multiplier(variables, objective, *constraints) -> Dict[str, sp.Rational]:
    """Sympy is kinda slow so this isn't actually a particulatly fast solution, but it's just cool to show that there's
    an (almost) analytic solution available."""
    lmbs = sp.symbols('lmb:{}'.format(len(constraints)))

    L = objective - sum(l * g for l, g in zip(lmbs, constraints))
    grad_L = [sp.diff(L, wrt) for wrt in (*variables, *lmbs)]  # Vector calc time
    candidates = sp.nsolve(grad_L, (*variables, *lmbs), [25 for i in (*variables, *lmbs)], dict=True)  # Stationary points of L

    # Find the optimal stationary point
    optimum = max(candidates, key=lambda assignment: objective.subs(assignment))
    return {var: optimum[var] for var in optimum if var in variables}


def discretise_solution(solution, objective, *constraints, neighbourhood=0) -> Tuple[int, Dict[str, int]]:
    """Takes a relaxed optimum, returns best attainable integer objective value, and the corresponding assignments.

    Neighbourhood argument determines the size of the area to explore, leave 0 for strictly convex problems"""
    floors = {var: int(solution[var]) for var in solution}
    headroom = BUDGET - sum(floors.values())

    candidates = itertools.product(*(range(floor - neighbourhood, floor + neighbourhood + headroom + 1) for floor in floors.values()))
    cand_maps = (dict(zip(solution.keys(), cand)) for cand in candidates)
    constrained_candidates = filter(lambda cand: all(cons.subs(cand) == 0 for cons in constraints), cand_maps)
    cand_scores = ((objective.subs(cand), cand) for cand in constrained_candidates)

    return max(cand_scores, key=lambda x: x[0])


def main():
    with open(sys.argv[1], 'r') as f:
        ingredients = dict(parse(line) for line in f)

    assignments, objective = symbolic_objective(ingredients)
    budget_constraint = sum(assignments) - BUDGET

    relaxed_soln = lagrange_multiplier(assignments, objective, budget_constraint)
    score, assignments = discretise_solution(relaxed_soln, objective, budget_constraint)
    print("Part 1 Score: {}\t\tRecipe: {}".format(score, assignments))

    caloric_constraint = sum(ingredients[str(x)]['calories'] * x for x in assignments) - CALORIE_BUDGET
    relaxed_soln = lagrange_multiplier(assignments, objective, budget_constraint, caloric_constraint)
    score, assignments = discretise_solution(relaxed_soln, objective, budget_constraint, caloric_constraint, neighbourhood=3)
    print("Part 2 Score: {}\t\tRecipe: {}".format(score, assignments))


if __name__ == "__main__":
    main()
