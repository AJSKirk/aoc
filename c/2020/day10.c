#include <stdio.h>
#include <stdlib.h>

#define MAX_ADAPTERS 128

int use_all(int *outputs, int len);
int compar(const void *a, const void *b);
long count_combinations(int *outputs,  int len);

int main(int argc, char* argv[]) {
	int len = 0;
	int outputs[MAX_ADAPTERS];
	
	outputs[0] = 0;  // Initial Jolts needed for part 2
	len++;
	while (scanf("%d\n", &outputs[len]) > 0) {
		if (len >= MAX_ADAPTERS) {
			printf("Buffer overflow!\n");
			exit(EXIT_FAILURE);
		}
		len++;
	}

	qsort(outputs, len, sizeof(int), compar);

	printf("Jolt Difference Product: %d\n", use_all(outputs, len));
	printf("Number of Possible Paths: %ld\n", count_combinations(outputs, len));

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


long count_combinations(int outputs[],  int len) {
	// Expects sorted array
	long paths[len];  // WARNING: Stack is fine here, but switch to calloc if needed for a larger problem
	int i, lookahead;

	paths[len-1] = 1;

	for (i=len-2; i>=0; i--)  {
		paths[i] = 0;
		lookahead = 1;
		while (lookahead <= 3  && lookahead + i < len && outputs[lookahead + i] - outputs[i] <= 3) {
			paths[i] += paths[i + lookahead++];
		}
	}

	return paths[0];
}

int compar(const void *a, const void *b) {
	const int a_val = *(int *) a, b_val = *(int *) b;
	return (a_val > b_val) - (a_val < b_val);
}
