import sys
from typing import List
from collections import namedtuple
import numpy as np


# Elements taken from http://www.se16.info/js/lands2.htm
ELEMENTS = (("H", "H", "22"),
            ("He", "Hf Pa H Ca Li", "13112221133211322112211213322112"),
            ("Li", "He", "312211322212221121123222112"),
            ("Be", "Ge Ca Li", "111312211312113221133211322112211213322112"),
            ("B", "Be", "1321132122211322212221121123222112"),
            ("C", "B", "3113112211322112211213322112"),
            ("N", "C", "111312212221121123222112"),
            ("O", "N", "132112211213322112"),
            ("F", "O", "31121123222112"),
            ("Ne", "F", "111213322112"),
            ("Na", "Ne", "123222112"),
            ("Mg", "Pm Na", "3113322112"),
            ("Al", "Mg", "1113222112"),
            ("Si", "Al", "1322112"),
            ("P", "Ho Si", "311311222112"),
            ("S", "P", "1113122112"),
            ("Cl", "S", "132112"),
            ("Ar", "Cl", "3112"),
            ("K", "Ar", "1112"),
            ("Ca", "K", "12"),
            ("Sc", "Ho Pa H Ca Co", "3113112221133112"),
            ("Ti", "Sc", "11131221131112"),
            ("V", "Ti", "13211312"),
            ("Cr", "V", "31132"),
            ("Mn", "Cr Si", "111311222112"),
            ("Fe", "Mn", "13122112"),
            ("Co", "Fe", "32112"),
            ("Ni", "Zn Co", "11133112"),
            ("Cu", "Ni", "131112"),
            ("Zn", "Cu", "312"),
            ("Ga", "Eu Ca Ac H Ca Zn", "13221133122211332"),
            ("Ge", "Ho Ga", "31131122211311122113222"),
            ("As", "Ge Na", "11131221131211322113322112"),
            ("Se", "As", "13211321222113222112"),
            ("Br", "Se", "3113112211322112"),
            ("Kr", "Br", "11131221222112"),
            ("Rb", "Kr", "1321122112"),
            ("Sr", "Rb", "3112112"),
            ("Y", "Sr U", "1112133"),
            ("Zr", "Y H Ca Tc", "12322211331222113112211"),
            ("Nb", "Er Zr", "1113122113322113111221131221"),
            ("Mo", "Nb", "13211322211312113211"),
            ("Tc", "Mo", "311322113212221"),
            ("Ru", "Eu Ca Tc", "132211331222113112211"),
            ("Rh", "Ho Ru", "311311222113111221131221"),
            ("Pd", "Rh", "111312211312113211"),
            ("Ag", "Pd", "132113212221"),
            ("Cd", "Ag", "3113112211"),
            ("In", "Cd", "11131221"),
            ("Sn", "In", "13211"),
            ("Sb", "Pm Sn", "3112221"),
            ("Te", "Eu Ca Sb", "1322113312211"),
            ("I", "Ho Te", "311311222113111221"),
            ("Xe", "I", "11131221131211"),
            ("Cs", "Xe", "13211321"),
            ("Ba", "Cs", "311311"),
            ("La", "Ba", "11131"),
            ("Ce", "La H Ca Co", "1321133112"),
            ("Pr", "Ce", "31131112"),
            ("Nd", "Pr", "111312"),
            ("Pm", "Nd", "132"),
            ("Sm", "Pm Ca Zn", "311332"),
            ("Eu", "Sm", "1113222"),
            ("Gd", "Eu Ca Co", "13221133112"),
            ("Tb", "Ho Gd", "3113112221131112"),
            ("Dy", "Tb", "111312211312"),
            ("Ho", "Dy", "1321132"),
            ("Er", "Ho Pm", "311311222"),
            ("Tm", "Er Ca Co", "11131221133112"),
            ("Yb", "Tm", "1321131112"),
            ("Lu", "Yb", "311312"),
            ("Hf", "Lu", "11132"),
            ("Ta", "Hf Pa H Ca W", "13112221133211322112211213322113"),
            ("W", "Ta", "312211322212221121123222113"),
            ("Re", "Ge Ca W", "111312211312113221133211322112211213322113"),
            ("Os", "Re", "1321132122211322212221121123222113"),
            ("Ir", "Os", "3113112211322112211213322113"),
            ("Pt", "Ir", "111312212221121123222113"),
            ("Au", "Pt", "132112211213322113"),
            ("Hg", "Au", "31121123222113"),
            ("Tl", "Hg", "111213322113"),
            ("Pb", "Tl", "123222113"),
            ("Bi", "Pm Pb", "3113322113"),
            ("Po", "Bi", "1113222113"),
            ("At", "Po", "1322113"),
            ("Rn", "Ho At", "311311222113"),
            ("Fr", "Rn", "1113122113"),
            ("Ra", "Fr", "132113"),
            ("Ac", "Ra", "3113"),
            ("Th", "Ac", "1113"),
            ("Pa", "Th", "13"),
            ("U", "Pa", "3"))


Element = namedtuple('Element', ["number", "children", "literal", "length"])


def literal_to_element(s: str) -> (int, str):
    """Takes a numeric string and returns the elemental name for it. Raises an error if s is not a single element"""
    assert s.isnumeric()
    for idx, (element, children, literal) in enumerate(ELEMENTS):
        if literal == s:
            return idx, element

    raise ValueError("Literal is not an element")


def create_matrices():
    """Generate one-step transition matrix and matrix of element lengths"""
    transition = np.array([[children.split().count(ELEMENTS[idx][0]) for idx in range(len(ELEMENTS))]
                           for element, children, literal in ELEMENTS], dtype=np.uint64)
    lengths = np.array([len(literal) for element, children, literal in ELEMENTS])
    return transition, lengths


def main():
    with open(sys.argv[1], 'r') as f:
        start_str = f.read().strip()
    start_idx, start_element = literal_to_element(start_str)
    start_vec = np.array([idx == start_idx for idx in range(len(ELEMENTS))], dtype=np.uint64)

    transition, lengths = create_matrices()

    for steps in (40, 50):
        full_transition = np.linalg.matrix_power(transition, steps)
        print("Length After {} Steps: {:>7}".format(steps, int(start_vec.dot(full_transition).dot(lengths))))


if __name__ == "__main__":
    main()
