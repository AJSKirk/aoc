#include <stdio.h>
#include <stdlib.h>

int get_file_length(FILE *fp) {
	int len = 0;
	char next_char;

	while (!feof(fp)) {
		next_char = fgetc(fp);
		if (next_char == '\n') {
			len++;
		}
	}
	return len;
}

int main(int argc, char* argv[]) {
	FILE *fp;
	int file_length;
	int* expenses;
	int next_expense;
	int i; int n;

	if (argc != 2) {
		printf("Usage: day1 <input.txt>");
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Unable to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	file_length= get_file_length(fp);
	printf("File length %i\n", file_length);

	return 0;
}


