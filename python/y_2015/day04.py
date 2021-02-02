import sys
import itertools
from hashlib import md5


def compute_hash(secret_key: str, addendum: int) -> str:
    guess = secret_key + str(addendum)
    return md5(guess.encode()).hexdigest()


def crack_hash(secret_key, leading_zeroes, start: int = 0) -> int:
    target = '0' * leading_zeroes
    return next(addendum for addendum in itertools.count(start)
                if compute_hash(secret_key, addendum).startswith(target))


def main():
    secret_key = sys.argv[1]
    first_answer = crack_hash(secret_key, 5)
    print(first_answer)
    print(crack_hash(secret_key, 6, first_answer))


if __name__ == "__main__":
    main()
