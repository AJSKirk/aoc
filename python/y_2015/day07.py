import operator
import re
import sys
from typing import Dict


OPERATIONS = {'AND': operator.and_,
              'NOT': operator.invert,
              'OR': operator.or_,
              'LSHIFT': operator.lshift,
              'RSHIFT': operator.rshift,
              '': lambda x: x}


Circuit = Dict[str, 'Wire']


class Wire:
    def __init__(self, op, inputs, circuit):
        self.op = op
        self.inputs = [i for i in inputs if i]
        self.circuit = circuit
        self.reset()

    def reset(self):
        self._value = None

    @property
    def value(self):
        if self._value is None:
            self._value = self._calc_value()

        return self._value

    def _calc_value(self):
        return self.op(*(int(w) if w.isnumeric() else self.circuit[w].value for w in self.inputs))


def parse(line: str, op_set: Dict, circuit: Circuit) -> (str, Wire):
    left, opcode, right, dest = re.match(r"([a-z0-9]*) ?([A-Z]*) ?([a-z0-9]*) -> (.+)", line).groups()

    return dest, Wire(op_set[opcode], (left, right), circuit)


def main():
    circuit = dict()
    with open(sys.argv[1], 'r') as f:
        circuit.update(parse(line, OPERATIONS, circuit) for line in f)

    # I am the egg man
    print("Part 1 Value: {}".format(short_val := circuit['a'].value))
    # I am the walrus

    # Reset circuit and override B val to the Part 1 answer
    for wire in circuit.values():
        wire.reset()
    circuit['b'] = Wire(OPERATIONS[''], (str(short_val),), circuit)

    print("Part 2 Value: {}".format(circuit['a'].value))


if __name__ == "__main__":
    main()
