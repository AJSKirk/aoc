#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_passport(char * passport);

int main(int argc, char* argv[]) {
	char passport[1024], row[256];
	int valid = 0, p_cursor = 0;
	char *next_row;

	while (1) {
		next_row = fgets(row, 255, stdin);
		if (next_row == NULL || *row == '\n') {
			p_cursor = 0;
			valid += check_passport(passport);
		} else {
			passport[p_cursor - 1] = ' '; // Hacky but it works
			strncpy(&passport[p_cursor], row, 255 - p_cursor); 
			p_cursor += strnlen(row, 255);
		}

		if (next_row == NULL) break;
	}

	printf("%d\n", valid);
	// printf("Multiplied Trees Encountered: %ld\n", trees_multiplied);
}

int check_passport(char * passport) {
	char fields[7][10] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
	int valid_fields[7] = {0, 0, 0, 0, 0, 0, 0};
	int num_fields = 7, i;
	char *pair, *field, *context = passport;
	
	pair = strtok_r(context, " ", &context);
	do {
		field = strtok(pair, ":");
		for (i=0; i<num_fields; i++) {
			if (strcmp(field, fields[i]) == 0) valid_fields[i] = 1;
		}
		pair = strtok_r(context, " ", &context);
	} while (pair != NULL);

	for (i=0; i<num_fields; i++) {
		if (valid_fields[i] == 0) return 0;
	}
	return 1;
}
