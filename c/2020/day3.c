#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_width(char* row);

int main(int argc, char* argv[]) {
	FILE* fp;
	char row[50];
	int colnum = 0, width = 0;
	int slopes[5] = {1, 3, 5, 7, 1};
	int cols[5] = {0, 0, 0, 0, 0}, trees[5] = {0, 0, 0, 0, 0};
	int rownum = 0, i;
    long trees_multiplied = 1; // Having this as an int really messed me up at first!

	clock_t start = clock();

	if (argc != 2) {
		printf("Usage: day2 <password_file>");
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Unable to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%49s\n", row);
	width = get_width(row);
	rewind(fp);

	while (fscanf(fp, "%49s\n", row) > 0) {
		for (i=0; i<4; i++) {
			if (row[cols[i] % width] == '#') trees[i] += 1;
			cols[i] += slopes[i];
		}
		
		if (rownum % 2 == 0) {
			if (row[cols[4] % width] == '#') trees[4]++;
			cols[4] += slopes[4];
		}
		rownum++;
	}

	for (i=0; i<5; i++) trees_multiplied *= trees[i];
	for (i=0; i<5; i++) printf("%d\n", trees[i]);

	printf("Trees Encountered: %d\n", trees[1]);
	printf("Multiplied Trees Encountered: %ld\n", trees_multiplied);
	printf("\nTotal runtime: %f ms\n", 1000 * (double) (clock() - start) / CLOCKS_PER_SEC);
}

int get_width(char* row) {
	int i = 0;
	while (row[i] != '\0') i++;
	return i;
}
