import sys
import itertools
from hashlib import md5
import multiprocessing


CHECK_FREQ = 10000


def compute_hash(secret_key: str, addendum: int) -> str:
    guess = secret_key + str(addendum)
    return md5(guess.encode()).hexdigest()


def crack_worker(secret_key, leading_zeroes, start, step, smallest):
    """Terminates once finding a working hash, or if it passes the current winner
    Checks current winner every CHECK_FREQ iterations to reduce lock delays"""
    target = '0' * leading_zeroes
    for i, addendum in enumerate(itertools.count(start, step)):
        if compute_hash(secret_key, addendum).startswith(target):
            if smallest.value == 0 or addendum < smallest.value:
                smallest.value = addendum
            return
        if i % CHECK_FREQ == 0 and smallest.value != 0 and addendum >= smallest.value:
            return


def crack_hash(secret_key, leading_zeroes, start=0) -> int:
    smallest = multiprocessing.Value('i', 0)
    num_cores = multiprocessing.cpu_count()
    threads = [multiprocessing.Process(target=crack_worker,
                                       args=(secret_key, leading_zeroes, start + increment, num_cores, smallest))
               for increment in range(num_cores)]

    for thread in threads:
        thread.start()

    for thread in threads:  # Wait for all threads to finish
        thread.join()

    return smallest.value


def main():
    secret_key = sys.argv[1]
    first_answer = crack_hash(secret_key, 5)
    print(first_answer)
    print(crack_hash(secret_key, 6, first_answer))


if __name__ == "__main__":
    main()
