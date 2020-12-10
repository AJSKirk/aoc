#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ADAPTERS 128

int use_all(int *outputs, int len);
int compar(const void *a, const void *b);
long count_combinations(int *outputs,  int len);

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
	printf("%ld\n", count_combinations(outputs, len));
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

long count_combinations(int outputs[],  int len) {
	// Expects sorted array
	//long paths[len];
	long *paths;
	int i, lookahead;

	paths = calloc(len, sizeof(long));
	paths[len-1] = 1;

	for (i=len-2; i>=0; i--)  {
		for (lookahead=1; lookahead<=3; lookahead++) {
			if (i + lookahead >= len || outputs[i + lookahead] - outputs[i] > 3) {
				break;
			}
			paths[i] += paths[i + lookahead];
		}
	}

	return paths[0];
}

int compar(const void *a, const void *b) {
	const int a_val = *(int *) a, b_val = *(int *) b;
	return (a_val > b_val) - (a_val < b_val);
}
