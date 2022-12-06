import fileinput


def packet_start_marker_loc(stream: str, packet_length=4) -> int:
    consec_iterator = zip(*(stream[n:] for n in range(packet_length)))
    return next(i for i, wdw in enumerate(consec_iterator, packet_length) if len(set(wdw)) == packet_length)


def main():
    stream = fileinput.input().readline().strip()
    print(f"Packet Start Marker: {packet_start_marker_loc(stream, 4)}")
    print(f"Message Start Marker: {packet_start_marker_loc(stream, 14)}")


if __name__ == "__main__":
    main()
