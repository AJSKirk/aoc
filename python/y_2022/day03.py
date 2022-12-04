import fileinput


def priority(item: str) -> int:
    if ord(item) >= ord('a'):
        return ord(item) - ord('a') + 1
    else:
        return ord(item) - ord('A') + 27


def find_duplicate(backpack: str) -> str:
    halfway = len(backpack) // 2
    dupe = set(item for item in backpack[:halfway] if item in backpack[halfway:])
    assert len(dupe) == 1
    return dupe.pop()


def slicer(xs, slice_length):
    return (xs[i:i+slice_length] for i in range(0, len(xs), slice_length))


def find_badges(backpacks) -> str:
    return set.intersection(*(set(b) for b in backpacks)).pop()  # Neat little one-liner


def main():
    backpacks = [line.strip() for line in fileinput.input()]
    print(sum(priority(find_duplicate(b)) for b in backpacks))
    print(sum(priority(find_badges(bs)) for bs in slicer(backpacks, 3)))


if __name__ == "__main__":
    main()
