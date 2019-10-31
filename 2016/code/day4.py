import sys
import termcolor_util as tc
from collections import namedtuple, Counter


class Room(namedtuple('Room', ['name', 'sector', 'checksum'])):
    """
    >>> r = Room(name='aaaaabbbzyx', sector=123, checksum='abxyz')
    >>> r.is_valid
    True
    >>> r = Room(name='totally-real-room', sector=200, checksum='decoy')
    >>> r.is_valid
    False
    """
    @property
    def is_valid(self):
        counter = Counter(c for c in self.name if c != '-')
        tops = ''.join([k for k, v in sorted(counter.items(), key=lambda x: (-x[1], x[0]), reverse=False)][:5])
        return tops == self.checksum

    @property
    def decrypted_name(self):
        """
        >>> r = Room(name='qzmt-zixmtkozy-ivhz', sector=343, checksum='')
        >>> r.decrypted_name
        'very encrypted name'
        """
        def shift_char(char, by):
            if char == '-': return ' '
            return chr(97 + (ord(char) - 97 + by) % 26)

        moves = self.sector % 26
        return ''.join(shift_char(char, moves) for char in self.name)


def parse_room(room_string):
    """
    >>> parse_room('aaaaa-bbb-z-y-x-123[abxyz]')
    Room(name='aaaaa-bbb-z-y-x', sector=123, checksum='abxyz')
    """
    name_sector, checksum = room_string.split('[')
    checksum = checksum[:-1]
    name_sector = name_sector.split('-')
    sector = int(name_sector.pop())
    name = '-'.join(name_sector)
    
    return Room(name, sector, checksum)
    

def load_input(fname):
    with open(fname, 'r') as f:
        for line in f.readlines():
            yield parse_room(line.strip())


def part_a(puzzle_input):
    return sum(room.sector for room in puzzle_input if room.is_valid)


def part_b(puzzle_input):
    for room in puzzle_input:
        if room.is_valid:
            print('{}    [{}]'.format(room.decrypted_name, room.sector))


def main(fname):
    puzzle_input = load_input(fname)
    print(f'The Answer to Part A is: {tc.green(part_a(puzzle_input))}')
    puzzle_input = load_input(fname)
    print(f'The Answer to Part B is: {tc.green(part_b(puzzle_input))}')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('USAGE: python [script.py] [input.txt]')
    else:
        main(sys.argv[1])
