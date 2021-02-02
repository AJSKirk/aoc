import sys
import itertools
from hashlib import md5
import multiprocessing


def compute_hash(secret_key: str, addendum: int) -> str:
    guess = secret_key + str(addendum)
    return md5(guess.encode()).hexdigest()


def crack_worker(secret_key, leading_zeroes, start, step, result):
    target = '0' * leading_zeroes
    result.put(next(addendum for addendum in itertools.count(start, step)
                    if compute_hash(secret_key, addendum).startswith(target)))


def crack_hash(secret_key, leading_zeroes, start=0) -> int:
    result = multiprocessing.Queue()
    num_cores = multiprocessing.cpu_count()
    threads = [multiprocessing.Process(target=crack_worker,
                                       args=(secret_key, leading_zeroes, start + step, num_cores, result))
               for step in range(num_cores)]

    for thread in threads:
        thread.start()

    out = result.get()
    for thread in threads:
        thread.terminate()

    return out


def main():
    secret_key = sys.argv[1]
    first_answer = crack_hash(secret_key, 5)
    print(first_answer)
    print(crack_hash(secret_key, 6, first_answer))


if __name__ == "__main__":
    main()
