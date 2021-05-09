import sys
import re
from collections import namedtuple

RACE_TIME = 2503

Reindeer = namedtuple('Reindeer', ['speed', 'move_time', 'rest_time'])


def parse(line: str):
    pattern = re.compile(r'(\w+) .+ (\d+) km/s for (\d+) .+ (\d+) seconds')
    name, *specs = re.match(pattern, line).groups()
    return name, make_generator(Reindeer(*(int(s) for s in specs)))


def make_generator(reindeer: Reindeer):
    """A Reindeer class might be more intuitive, but making generators to hold state seemed like more fun"""
    while True:
        for _ in range(reindeer.move_time):
            yield reindeer.speed
        for _ in range(reindeer.rest_time):
            yield 0


def main():
    reindeers = dict()  # Not strictly gramatically correct but "plural variables end in s" is a good convention
    with open(sys.argv[1], 'r') as f:
        reindeers.update(parse(line) for line in f)

    distances = {name: sum(step for _, step in zip(range(RACE_TIME), reindeers[name])) for name in reindeers}
    winner = max(distances, key=distances.get)

    print("The winner is {}, having travelled {} km".format(winner, distances[winner]))


if __name__ == '__main__':
    main()
