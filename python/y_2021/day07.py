import sys
from collections import Counter


def true_fuel_cost(start, end):
    n = abs(start - end)
    return n * (n + 1) // 2


def alignment_fuel(crabs: Counter, fuel_spend=lambda x, y: abs(x - y)) -> int:
    return min(sum(n_crabs * fuel_spend(point, end) for point, n_crabs in crabs.items()) for end in crabs.keys())


def main():
    crabs = Counter(int(crab) for crab in sys.stdin.read().strip().split(','))
    print(f"Total Fuel Required: {alignment_fuel(crabs)}")
    print(f"True Total Fuel Required: {alignment_fuel(crabs, true_fuel_cost)}")


if __name__ == "__main__":
    main()
