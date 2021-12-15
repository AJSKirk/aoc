import sys
from functools import reduce
from typing import List


def get_most_common_bits(diagnostic_report):
    report_length = len(diagnostic_report)
    row_length = len(diagnostic_report[0])
    column_sums = reduce(lambda state, row: [sum(el) for el in zip(state, row)],
                         diagnostic_report,
                         [0 for i in range(row_length)])

    return [int(count >= report_length / 2) for count in column_sums]


def bitmask_to_int(bitmask: List[int]) -> int:
    return int(''.join(str(bit) for bit in bitmask), 2)


def power_consumption(diagnostic_report):
    most_common_bits = get_most_common_bits(diagnostic_report)
    least_common_bits = [1 - mcb for mcb in most_common_bits]

    return bitmask_to_int(most_common_bits) * bitmask_to_int(least_common_bits)


def filter_bitwise(candidates, least_common=False):
    for bit in range(len(candidates[0])):
        matches = get_most_common_bits(candidates)
        if least_common:
            matches = [1 - mcb for mcb in matches]
        candidates = [cand for cand in candidates if cand[bit] == matches[bit]]
        if len(candidates) == 1:
            return candidates[0]

    raise ValueError("Failed to filter to unique value")


def life_support_rating(diagnostic_report):
    oxygen_rating = filter_bitwise(diagnostic_report.copy())
    co2_rating = filter_bitwise(diagnostic_report.copy(), True)

    return bitmask_to_int(oxygen_rating) * bitmask_to_int(co2_rating)


def main():
    diagnostic_report = [[int(c) for c in line.strip()] for line in sys.stdin]
    print(f"Power Consumption: {power_consumption(diagnostic_report)}")
    print(f"Life Support Rating: {life_support_rating(diagnostic_report)}")


if __name__ == "__main__":
    main()
