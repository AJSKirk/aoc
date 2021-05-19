import sys
import re
from collections import namedtuple
from typing import Dict, Generator

RACE_TIME = 2503

Reindeer = namedtuple('Reindeer', ['speed', 'move_time', 'rest_time'])


def parse(line: str):
    pattern = re.compile(r'(\w+) .+ (\d+) km/s for (\d+) .+ (\d+) seconds')
    name, *specs = re.match(pattern, line).groups()
    return name, make_generator(Reindeer(*(int(s) for s in specs)))


def make_generator(reindeer: Reindeer):
    """A Reindeer class might be more intuitive, but making generators to hold state seemed like more fun.
    Using stepwise simulations rather than an analytic answer."""
    dist = 0
    while True:
        for _ in range(reindeer.move_time):
            yield (dist := dist + reindeer.speed)
        for _ in range(reindeer.rest_time):
            yield dist


def run_race(reindeers: Dict[str, Generator]) -> (Dict[str, int], Dict[str, float]):
    """Return points, distances"""
    points = {name: 0 for name in reindeers}
    for _ in range(RACE_TIME):
        distances = {name: next(gen) for name, gen in reindeers.items()}
        leaders = (name for name in distances if distances[name] == max(distances.values()))
        for leader in leaders:
            points[leader] += 1

    return points, distances



def main():
    reindeers = dict()  # Not strictly gramatically correct but "plural variables end in s" is a good convention
    with open(sys.argv[1], 'r') as f:
        reindeers.update(parse(line) for line in f)

    points, distances = run_race(reindeers)
    winner = max(distances, key=distances.get)
    print("The winner is {}, having travelled {} km".format(winner, distances[winner]))

    winner = max(points, key=points.get)
    print("The new winner is {}, having accumulated {} points".format(winner, points[winner]))


if __name__ == '__main__':
    main()
