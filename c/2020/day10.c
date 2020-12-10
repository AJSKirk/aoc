#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ADAPTERS 128

int use_all(int *outputs, int len);
int compar(const void *a, const void *b);
long count_combinations(int *outputs,  int len, int target);

int main(int argc, char* argv[]) {
	int len = 0;
	int outputs[MAX_ADAPTERS];
	
	outputs[0] = 0;
	len++;
	while (scanf("%d\n", &outputs[len]) > 0) {
		if (len >= MAX_ADAPTERS) {
			printf("Buffer overflow!\n");
			exit(EXIT_FAILURE);
		}
		len++;
	}

	qsort(outputs, len, sizeof(int), compar);

	printf("%d\n", use_all(outputs, len));
	printf("%ld\n", count_combinations(outputs, len, outputs[len - 1] + 3));
	return 0;
}

int use_all(int *outputs, int len) {
	// Expects sorted array
	int deltas[4] = {0, 0, 0, 1};  // Final jump included here
	int i, last = 0;

	for (i=0; i<len; i++) {
		deltas[outputs[i] - last]++;
		last = outputs[i];
	}

	return deltas[1] * deltas[3];

}

/*int locate_cuts(int *outputs, len) {
	int i;

	for (i=0; i<len; i++) {
		if

	}
}*/

long count_combinations(int outputs[],  int len, int target) {
	// Expects sorted array
	int lookahead, paths=0;
	
	if (len == 1)
		return 1;

	for (lookahead=1; lookahead<=3; lookahead++) {
		if (lookahead > len || outputs[lookahead] - outputs[0] > 3) {
			return paths;
		}
		paths += count_combinations(&outputs[lookahead], len - lookahead, target);
	}
	return paths;
}

int compar(const void *a, const void *b) {
	const int a_val = *(int *) a, b_val = *(int *) b;
	return (a_val > b_val) - (a_val < b_val);
}
