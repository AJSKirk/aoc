#include <stdio.h>

int get_file_length(FILE *fp) {
	int len = 0;
	char next_char;
	
	while (!feof(fp)) {
		next_char = fgetc(fp);
		if (next_char == '\n') {
			len++
		}
	}
	return len;
}

int main(int argc, char* argv[]) {
	FILE *fp;
	int file_length;
	int* expenses;
	int next_expense;
	int i;

	if (argc != 2) {
		printf("Usage: day1 <input.txt.");
	}

	fp = fopen(argv[1], 'r');
	if (fp == NULL) {
		printf("Could not allocate file pointer");
		exit(EXIT_FAILURE);
	}

	file_length = get_file_length(fp);
	
	expenses = (int*) malloc(file_length * sizeof(int));
	if (expenses == NULL) {
		printf("Could not allocate memory for expense reports");
		exit(EXIT_FAILURE);
	}

	rewind(fp);
	i = 0; n = 0;
	while (fscanf(fp, "%d\n", &n) > 0) {
		expenses[i] = n;
		i++;
	}
}


