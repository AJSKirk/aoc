#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int check_passport(char * passport);
int check_passport_strict(char * passport);

int main(int argc, char* argv[]) {
	char passport[1024], row[256];
	int valid = 0, valid_strict = 0, p_cursor = 0, len = 0;
char *next_row;

	do {
		next_row = fgets(row, 255, stdin);
		if (next_row == NULL || *row == '\n') {
			p_cursor = 0;
			valid += check_passport(passport);
			valid_strict += check_passport_strict(passport);
		} else {
			len = strnlen(row, 255);
			row[len -  1] = ' '; // Hacky but it works to drop the newline
			strncpy(&passport[p_cursor], row, 255 - p_cursor); 
			p_cursor += strnlen(row, 255);
		}

	} while (next_row != NULL);

	printf("Valid Documents: %d\n", valid);
	printf("Strict Valid Documents: %d\n", valid_strict);
}

int check_passport(char * passport) {
	const char *fields[7];
	regex_t pattern;
	int num_fields = 7, i;

	fields[0] = "byr"; fields[1] = "iyr"; fields[2] = "eyr"; fields[3] = "hgt";
	fields[4] = "hcl"; fields[5] = "ecl"; fields[6] = "pid";

	for (i=0; i<num_fields; i++) {
		regcomp(&pattern, fields[i], REG_EXTENDED);
		if (regexec(&pattern, passport, 0, NULL, 0) != 0) {
			regfree(&pattern);
			return 0;
		}
		regfree(&pattern);
	}
	return 1;
}

int check_passport_strict(char* passport) {
	const char *fields[7];
	regex_t pattern;
	int num_fields = 7, i;
	
	fields[0] = "byr:(19([2-9][0-9])|200(0|1|2)) ";
	fields[1] = "iyr:(20(1[0-9]|20)) ";
	fields[2] = "eyr:(20(2[0-9]|30)) ";
	fields[3] = "hgt:(1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in) ";
	fields[4] = "hcl:#[a-f0-9]{6} ";
	fields[5] = "ecl:(amb|blu|brn|gry|grn|hzl|oth) ";
	fields[6] = "pid:[0-9]{9} ";

	for (i=0; i<num_fields; i++) {
		regcomp(&pattern, fields[i], REG_EXTENDED);
		if (regexec(&pattern, passport, 0, NULL, 0) != 0) {
			regfree(&pattern);
			return 0;
		}
		regfree(&pattern);
	}
	return 1;
}


