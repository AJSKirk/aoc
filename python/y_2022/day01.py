import sys


def main():
    sorted_calories = sorted(calorie_counts(sys.stdin), reverse=True)
    print(f"Max Calories: {sorted_calories[0]}")
    print(f"Top 3 Total: {sum(sorted_calories[:3])}")


def calorie_counts(lines):
    total = 0
    for line in lines:
        if line.strip() == '':
            yield total
            total = 0
        else:
            total += int(line.strip())

    yield total  # Don't forget the last elf!


if __name__ == "__main__":
    main()
