#include <stdio.h>
#include <stdlib.h>

#define GLOBAL_TARGET 2020
#define BUFFER_LENGTH 1024

int compar(const void *a, const void *b);
int twosum(int *arr, int len, int target);
int threesum(int *arr, int len, int target);

int main(int argc, char* argv[]) {
	int expenses[BUFFER_LENGTH];
	int len = 0;

	while (scanf("%d", &expenses[len]) > 0) {
		len++;
	}

	qsort(expenses, len, sizeof(int), compar);

	printf("The product of the matching entries is: %i\n", twosum(expenses, len, GLOBAL_TARGET));
	printf("The product of the matching entries is: %i\n", threesum(expenses, len, GLOBAL_TARGET));

	return 0;
}

int compar(const void *a, const void *b) {
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
	int lhs = 0, rhs = len, subres, boundsum;

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
