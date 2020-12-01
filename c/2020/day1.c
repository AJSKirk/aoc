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
	int i; int j; int n;

	if (argc != 2) {
		printf("Usage: day1 <input.txt>");
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Unable to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	file_length= get_file_length(fp);

	expenses= (int*) malloc(file_length * sizeof(int));

	rewind(fp);
	i = 0;
	while (fscanf(fp, "%d/n", &n) > 0) {
		expenses[i] = n;
		i++;
	}

	for (i=0; i < file_length; i++) {
		for (j=i+1; j < file_length; j++) {
			if (expenses[i] + expenses[j] == 2020) {
				printf("The product of the matching entries is: %i\n", expenses[i] * expenses[j]);
				break;
			}
		}
	} // Should really find a way to break out of this outer loop

	return 0;
}


