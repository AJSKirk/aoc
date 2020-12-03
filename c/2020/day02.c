#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_valid(char* passwd, char target, int min, int max);
int new_valid(char* passwd, char target, int* positions, int num_pos);

int main(int argc, char* argv[]) {
	int min, max, valid = 0, valid2 = 0;
	char target, passwd[50];
	int positions[2];
	clock_t start = clock();

	if (argc != 1) {
		printf("Usage: day2 < <password_file>\n");
		exit(EXIT_FAILURE);
	}

	/* Iterate over file and check each password against each validity test
	 * Could check on the fly without putting password in memory, but we're getting
	 * L1 caching anyway so speedup not worth the misery
	 */
	while (scanf("%d-%d %c: %s\n", &min, &max, &target, passwd) > 0) {
		valid += is_valid(passwd, target, min, max);
		positions[0] = min; positions[1] = max;
		valid2 += new_valid(passwd, target, positions, 2);
	}

	printf("Valid Passwords: %d\n", valid);
	printf("Valid Passwords Under New Policy: %d\n", valid2);
	printf("\nTotal runtime: %f ms\n", 1000 * (double) (clock() - start) / CLOCKS_PER_SEC);
}

int is_valid(char* passwd, char target, int min, int max) {
	int i = 0, count = 0;

	while (passwd[i] != '\0') {
		if (passwd[i] == target) count++;
		if (count > max) return 0;
		i++;
	}

	if (count >= min) return 1;
	else return 0;
}

int new_valid(char* passwd, char target, int* positions, int num_pos) {
	int i, count = 0;

	for (i=0; i<num_pos; i++) {
		if (passwd[positions[i] - 1] == target) count++;
		if (count > 1) return 0;
	}
	return count; // This is a valid test - 1->1 and 0->0
}

