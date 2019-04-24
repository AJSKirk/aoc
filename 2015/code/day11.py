import sys
import termcolor_util as tc


class Password:
    def __init__(self, text):
        self.text = text

    def increment(self, pos=-1):
        #  Should move at least the IOL filter up here for speed
        if self.text[pos] == 'z':
            self.text = f"{self.text[:pos]}{'a'}{self.text[pos:][1:]}"
            self.increment(pos=pos - 1)
        else:
            self.text = f"{self.text[:pos]}{chr(ord(self.text[pos]) + 1)}{self.text[pos:][1:]}"

    @property
    def is_valid_a(self):
        if any(invalid in self.text for invalid in 'iol'):
            return False

        doubles = set()
        for c1, c2 in zip(self.text[:-1], self.text[1:]):
            if c1 == c2:
                doubles.add(c1)
        if len(doubles) < 2:
            return False

        for c1, c2, c3 in zip(self.text[:-2], self.text[1:-1], self.text[2:]):
            if ord(c3) - ord(c2) == ord(c2) - ord(c1) == 1:
                return True

        return False


def part_a(password):
    while not password.is_valid_a:
        password.increment()
    return password.text


def part_b(password):
    pass


def main(password_text):
    password = Password(password_text)
    print(f'The Answer to Part A is: {tc.green(part_a(password))}')
    print(f'The Answer to Part B is: {tc.green(part_b(password))}')


if __name__ == '__main__':
    if len(sys.argv) not in (2, 3):
        print('USAGE: python [script.py] [sequence]')
    else:
        main(*sys.argv[1:])
