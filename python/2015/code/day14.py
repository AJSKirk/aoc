import sys
import termcolor_util as tc
from collections import namedtuple
import re


class Reindeer(namedtuple('Reindeer', ['name', 'speed', 'stamina', 'recharge'])):
    def __init__(self, name, speed, stamina, recharge):
        super().__init__()
        self.points = 0

    def distance_covered(self, time):
        time_remaining = time
        dist = 0
        while time_remaining >= self.stamina:
            dist += self.speed * self.stamina
            time_remaining -= self.stamina + self.recharge
        dist += self.speed * max(0, time_remaining)
        return dist

    def add_point(self):
        self.points += 1


def load_input(fname):
    reindeers = set()
    with open(fname, 'r') as f:
        for line in f:
            name = line.split(' ')[0]
            speed, stamina, recharge = [int(x) for x in re.findall('[0-9]+', line)]
            reindeers.add(Reindeer(name, speed, stamina, recharge))

    return reindeers


def part_a(reindeers, time):
    return max(reindeer.distance_covered(time) for reindeer in reindeers)


def part_b(reindeers, time):
    """Cumbersome full hist sim at each timestep, a consequence of how I solved Part A.
    Should definitely be improved, but not burdensome for problem of this size (knowing when to STOP optimizing
    is a valuable skill too!)"""
    for step in range(1, time):
        # Multi-step logic deals with ties, should be a better way to do it though
        scores = {reindeer: reindeer.distance_covered(step) for reindeer in reindeers}
        winning_score = max(scores.values())
        for reindeer in reindeers:
            if scores[reindeer] == winning_score:
                reindeer.add_point()

    return max(reindeer.points for reindeer in reindeers)


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input, 2503))}')
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input, 2503))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(*sys.argv[1:])
