#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
	char row[50];
	int colnum = 0, width = 0, nslopes = 5;
	int delta_cols[5] = {1, 3, 5, 7, 1}, delta_rows[5] = {1, 1, 1, 1, 2};
	int cols[5] = {0, 0, 0, 0, 0}, trees[5] = {0, 0, 0, 0, 0};
	int rownum = 0, i;
	long trees_multiplied = 1; // Having this as an int really messed me up at first!

	while (scanf("%49s\n", row) > 0) {
		if (width == 0) width = (int) strnlen(row, 50);
		for (i=0; i<nslopes; i++) {
			if (rownum % delta_rows[i] == 0) {
				if (row[cols[i] % width] == '#') trees[i] += 1;
				cols[i] += delta_cols[i];
			}
		}
		rownum++;
	}

	for (i=0; i<nslopes; i++) trees_multiplied *= trees[i];

	printf("Trees Encountered: %d\n", trees[1]);
	printf("Multiplied Trees Encountered: %ld\n", trees_multiplied);
}
