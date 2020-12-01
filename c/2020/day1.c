#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void file_to_arr(FILE* fp, int* arr) {
	int i, n;

	i = 0;
	while (fscanf(fp, "%d/n", &n) > 0) {
		arr[i] = n;
		i++;
	}
	return;
}

int compar(const void* a, const void *b) {
	const int a_val = *(int*) a, b_val = *(int*) b;
	return (a_val > b_val) - (a_val < b_val);
}

int twosum(int* arr, int len, int target) {
	// Expects sorted array
	int lhs = 0, rhs = len - 1, sum;

	while (lhs < rhs) {
		sum = arr[lhs] + arr[rhs];
		if (sum == target) return arr[lhs] * arr[rhs];
		else if (sum < target) lhs++; // Too small, get bigger
		else rhs--; // Too big, get smaller
	}
	return -1; // Fail code
}

int threesum(int* arr, int len, int target) {
	int lhs, rhs = len, subres, boundsum;

	while (lhs < rhs) {
		boundsum = arr[lhs] + arr[rhs];
		if (boundsum >= target) {
			rhs--;
		}
		else {
			subres = twosum(&arr[lhs + 1], rhs - lhs - 1, target - arr[lhs]);
			if (subres > 0) return arr[lhs] * subres;
		}
	}
	return -1;
}


int main(int argc, char* argv[]) {
	FILE *fp;
	int file_length;
	int* expenses;
	clock_t start;

	start = clock();

	if (argc != 3) {
		printf("Usage: day1 <input.txt> <target_sum>");
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Unable to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	file_length = get_file_length(fp);

	expenses = (int*) malloc(file_length * sizeof(int));

	rewind(fp);
	file_to_arr(fp, expenses);

	qsort(expenses, file_length, sizeof(int), compar);

	printf("The product of the matching entries is: %i\n", twosum(expenses, file_length, atoi(argv[2])));
	printf("The product of the matching entries is: %i\n", threesum(expenses, file_length, atoi(argv[2])));
	printf("\nTotal runtime: %f ms\n", 1000 * (double) (clock() - start) / CLOCKS_PER_SEC);

	free(expenses);
	return 0;
}


