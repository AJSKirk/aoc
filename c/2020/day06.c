#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

typedef unsigned int set_t; // 4 bytes is plenty

set_t populate_set(const char *person);
unsigned int get_cardinality(set_t set);

int main(int argc, char* argv[]) {
	char group[256], person[32];
	int p_cursor = 0, len = 0;
	char *next_person;
	int total = 0, members = 0, total_strict = 0;
	set_t union_set = 0, intersection_set = 0, questions;

	while (1) {
		next_person = fgets(person, 32, stdin);
		if (next_person == NULL || *person == '\n') {
			total += get_cardinality(union_set);
			total_strict += get_cardinality(intersection_set);
			printf("%d\n", get_cardinality(intersection_set));
			union_set = 0;
			intersection_set = ~0;
		} else {
			person[strnlen(person, 32) - 1] = '\0'; // Drop the newline char
			questions = populate_set(person);
			union_set |= questions;
			intersection_set &= questions;
		}

		if (next_person == NULL) break;
	}

	printf("Total Count: %d\n", total);
	printf("Total Strict Count: %d\n", total_strict);
	return 0;
}

set_t populate_set(const char *person) {
	// Creates a bitmask-array implemented set for a person's answers
	set_t questions = 0;
	int i = 0, val_char;
	const int val_a = (int) 'a';

	while (person[i] != '\0') {
		val_char = ((int) person[i]) - val_a;
		questions |= (1U << val_char);  // Sets val_charth bit of questions to 1
		i++;
	}

	return questions;
}

unsigned int get_cardinality(set_t set) {
	int i, card = 0;

	for (i=0; i<8*sizeof(set_t); i++) { // Remember sizeof is bytes, not bits
		card += 1U & (set >> i);
	}
	return card;
}
