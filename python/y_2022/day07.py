import fileinput
from dataclasses import dataclass, field


@dataclass
class PathObject:
    name: str
    children: list = field(default_factory=list)
    filesize: int = field(default=0)


def build_tree(input) -> PathObject:
    path = [PathObject('/')]
    for line in input:
        match line.strip().split():
            case ['$', 'cd', '..']:
                path.pop()
            case ['$', 'cd', '/']:
                del path[1:]
            case ['$', 'cd', newdir_name]:
                newdir = PathObject(newdir_name)
                path[-1].children.append(newdir)
                path.append(newdir)
            case [size, name] if size.isnumeric():
                path[-1].filesize += int(size)

    return path[0]


def get_sizes(root):
    size = root.filesize
    for child in root.children:
        size += yield from get_sizes(child)

    yield size
    return size


def main():
    tree = build_tree(fileinput.input())
    sizes = list(get_sizes(tree))
    print(f"Sum of Small Dirs: {sum(size for size in sizes if size <= 100000)}")
    print(f"To Delete: {next(size for size in sorted(sizes) if size >= sizes[-1] - 40000000)}")


if __name__ == "__main__":
    main()
