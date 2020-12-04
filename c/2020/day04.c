#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_passport(char * passport);
int check_passport_strict(char * passport);

int main(int argc, char* argv[]) {
	char passport[1024], row[256];
	int valid = 0, p_cursor = 0, len = 0;
	char *next_row;

	while (1) {
		next_row = fgets(row, 255, stdin);
		if (next_row == NULL || *row == '\n') {
			p_cursor = 0;
			valid += check_passport_strict(passport);
		} else {
			len = strnlen(row, 255);
			row[len -  1] = ' '; // Hacky but it works to drop the newline
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

int check_passport_strict(char* passport) {
	char *pair, *field, *value, *context = passport;
	int valid_fields[7] = {0, 0, 0, 0, 0, 0, 0};
	int i, num_fields = 7, len, hgt, year;

	pair = strtok_r(context, " ", &context);
	do {
		field = strtok(pair, ":");
		value = strtok(NULL, " ");
		if (strcmp(field, "byr") == 0) {
			year = atoi(value);
			if (year < 1920 || year > 2002 || strnlen(value, 32) != 4) return 0;
			valid_fields[0] = 1;
		} else if (strcmp(field, "iyr") == 0) {
			year = atoi(value);
			if (year < 2010 || year > 2020 || strnlen(value, 32) != 4) return 0;
			valid_fields[1] = 1;
		} else if (strcmp(field, "eyr") == 0) {
			year = atoi(value);
			if (year < 2020 || year > 2030 || strnlen(value, 32) != 4) return 0;
			valid_fields[2] = 1;
		} else if (strcmp(field, "hgt") == 0) {
			hgt = atoi(value);
			len = strnlen(value, 32);
			if (strcmp(&value[len - 2], "cm") == 0) {
				if (hgt < 150 || hgt > 193) return 0;
			} else if (strcmp(&value[len - 2], "in") == 0) {
				if (hgt < 59 || hgt > 76) return 0;
			} else return 0;
			valid_fields[3] = 1;
		} else if (strcmp(field, "hcl") == 0) {
			if (*value != '#' || strnlen(value, 32) != 7) return 0;
			for (i=1;i<7;i++) {
				if (isalnum(value[i]) == 0) return 0;
			}
			valid_fields[4] = 1;
		} else if (strcmp(field, "ecl") == 0) {
			if (strcmp(value, "amb") == 0) {
				valid_fields[5] += 1;
			} else if (strcmp(value, "blu") == 0) {
				valid_fields[5] += 1;
			} else if (strcmp(value, "brn") == 0) {
				valid_fields[5] += 1;
			} else if (strcmp(value, "gry") == 0) {
				valid_fields[5] += 1;
			} else if (strcmp(value, "grn") == 0) {
				valid_fields[5] += 1;
			} else if (strcmp(value, "hzl") == 0) {
				valid_fields[5] += 1;
			} else if (strcmp(value, "oth") == 0) {
				valid_fields[5] += 1;
			} else return 0;
		} else if (strcmp(field, "pid") == 0) {
			if (strnlen(value, 10) != 9) return 0;
			for (i=0; i<9; i++) {
				if (isdigit(value[i]) == 0) return 0;
			}
			valid_fields[6] = 1;
		}

		pair = strtok_r(context, " ", &context);
	} while (pair != NULL);

	for (i=0; i<num_fields; i++) {
		if (valid_fields[i] == 0) return 0;
	}
	return 1;
	return 1;
}


