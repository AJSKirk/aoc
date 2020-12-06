#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

int check_group(const char * group, int members);

int main(int argc, char* argv[]) {
	char group[256], row[32];
	int p_cursor = 0, len = 0;
	char *next_row;
	int total = 0, members = 0, total_strict = 0;

	while (1) {
		next_row = fgets(row, 32, stdin);
		if (next_row == NULL || *row == '\n') {
			p_cursor = 0;
			total += check_group(group, 1);
			total_strict += check_group(group, members);
			members = 0;
		} else {
			len = strnlen(row, 32);
			row[len -  1] = ' '; // Hacky but it works to drop the newline
			strncpy(&group[p_cursor], row, 255 - p_cursor); 
			p_cursor += len;
			members++;
		}

		if (next_row == NULL) break;
	}

	printf("Total Count: %d\n", total);
	printf("Total Strict Count: %d\n", total_strict);
	return 0;
}

int check_group(const char * group, int members) {
	// Set members=1 for Part 1
	/* Hash tables would be more general, but 26 bytes is a small
	 * price to pay for the speed here. Feel like it might bite me
	 * in Part 2 though */
	int letters[26] = {0};
	char current;
	int i = 0, total = 0, val_char;
	int val_a = (int) 'a';

	while (group[i] != '\0') {
		if (group[i] != ' ') { 
			val_char = ((int) group[i]) - val_a;
			letters[val_char]++;
		}
		i++;
	}

	for (i=0; i<26; i++) {
		total += (letters[i] >= members);
	}

	return total;
}

