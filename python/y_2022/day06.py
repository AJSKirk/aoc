import fileinput


def packet_start_marker_loc(stream: str, packet_length=4) -> int:
    consec_iterator = zip(*(stream[n:] for n in range(packet_length)))
    return next(i for i, wdw in enumerate(consec_iterator, packet_length) if len(set(wdw)) == packet_length)


def main():
    print(packet_start_marker_loc(fileinput.input().readline().strip()))


if __name__ == "__main__":
    main()
