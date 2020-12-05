#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <mpi.h>

#define MAX_PASSPORTS 512
#define PASSPORT_BUFFER 1024

int check_passport(char * passport);
int check_passport_strict(char * passport);

int main(int argc, char* argv[]) {
	char big_passports[MAX_PASSPORTS * PASSPORT_BUFFER], row[256];
	//char *passports;
	int num_passports = 0;
	int valid = 0, valid_strict = 0, p_cursor = 0, len = 0;
	int global_valid, global_valid_strict;
	char *next_row;

	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//passports = (char *) malloc((MAX_PASSPORTS * PASSPORT_BUFFER / size) * sizeof(char));
	char passports[MAX_PASSPORTS * PASSPORT_BUFFER / size];

	//big_passports = (char *) malloc(MAX_PASSPORTS * PASSPORT_BUFFER * sizeof(char));
	//row = (char *) malloc(256 * sizeof(char));

	if (rank == 0) {
		printf("Running on %d processes\n", size);
		while (1) {
			next_row = fgets(row, 255, stdin);
			if (next_row == NULL || *row == '\n') {
				p_cursor = ((p_cursor / PASSPORT_BUFFER) + 1) * PASSPORT_BUFFER;
				num_passports ++;
			} else {
				len = strnlen(row, 255);
				row[len -  1] = ' '; // Hacky but it works to drop the newline
				strncpy(&big_passports[p_cursor], row, 255 - (p_cursor % PASSPORT_BUFFER)); 
				p_cursor += strnlen(row, 255);
			}
			if (next_row == NULL) break;
		}
	}

	//num_passports = ((num_passports / size) + 1) * size;
	num_passports = MAX_PASSPORTS;


	MPI_Scatter(big_passports, num_passports * PASSPORT_BUFFER / size, MPI_CHAR,
			passports, num_passports * PASSPORT_BUFFER / size, MPI_CHAR, 0, MPI_COMM_WORLD);

	//if (rank == 0) free(big_passports);

	for (int i=0; i< num_passports / size; i++) {
		valid += check_passport(&passports[i * PASSPORT_BUFFER]);
		valid_strict += check_passport_strict(&passports[i * PASSPORT_BUFFER]);
	}

	MPI_Reduce(&valid, &global_valid, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&valid_strict, &global_valid_strict, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Valid Documents: %d\n", global_valid);
		printf("Strict Valid Documents: %d\n", global_valid_strict);
	}

	MPI_Finalize();
}

int check_passport(char * passport) {
	const char *fields[7];
	regex_t pattern;
	int num_fields = 7, i;

	fields[0] = "byr"; fields[1] = "iyr"; fields[2] = "eyr"; fields[3] = "hgt";
	fields[4] = "hcl"; fields[5] = "ecl"; fields[6] = "pid";

	for (i=0; i<num_fields; i++) {
		regcomp(&pattern, fields[i], REG_EXTENDED);
		if (regnexec(&pattern, passport, PASSPORT_BUFFER, 0, NULL, 0) != 0) {
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
		if (regnexec(&pattern, passport, PASSPORT_BUFFER, 0, NULL, 0) != 0) {
			regfree(&pattern);
			return 0;
		}
		regfree(&pattern);
	}
	return 1;
}


