#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#define PRECURSORS_LEN 25
#define SEEN_LEN 1024

int check_valid(long next,  long precursors[]);
void replace_precursor(long expired, long new, long sorted[]);
int compar(const void *a, const void *b);
long find_region(long *seen, int len, long target);

int main(int argc, char* argv[]) {
	int i = 0;
	long next, first_invalid = 0, expired = 0; // Too large for int!
	long precursors_seen[PRECURSORS_LEN] = {0}, precursors_sort[PRECURSORS_LEN] = {0};
	long seen[SEEN_LEN] = {0};
	
	struct timeval start, start_2, end;
	gettimeofday(&start, NULL);
	
	while (scanf("%ld\n", &next) > 0) {
		if (i >= PRECURSORS_LEN) {  // Skipped for preamble
			if (!check_valid(next, precursors_sort)) break;
			expired = precursors_seen[i % PRECURSORS_LEN];
		}

		if (i > SEEN_LEN) {
			printf("Seen buffer overflow!\n");
			exit(EXIT_FAILURE);
		}
		seen[i] = next;

		precursors_seen[i++ % PRECURSORS_LEN] = next;  // Start overwriting oldest
		replace_precursor(expired, next, precursors_sort);
		qsort(precursors_sort, PRECURSORS_LEN, sizeof(long), compar);
		// TODO: Replace with insertion sort - faster on nearly sorted data
	}

	printf("First Invalid Number: %ld\n", next);
	gettimeofday(&start_2, NULL);
	printf("Weakness: %ld\n", find_region(seen, i, next));
	gettimeofday(&end, NULL);

	printf("\nProblem 1 Time, including Parse: %d microseconds\n", start_2.tv_usec - start.tv_usec);
	printf("Problem 2 Time: %d microseconds\n", end.tv_usec - start_2.tv_usec);
	return 0;
}

void replace_precursor(long expired, long new, long sorted[]) {
	// We know the list is sorted so we can binary search
	int *mid = NULL;

	mid = bsearch(&expired, sorted, PRECURSORS_LEN, sizeof(long), compar);
	if (mid == NULL) {
		printf("Search for element %ld failed\n", expired);
		exit(EXIT_FAILURE);
	}
	*mid = new;
}

int compar(const void *a, const void *b) {
	const long a_val  = *(long *) a, b_val = *(long *) b;
	return (a_val > b_val) - (a_val < b_val);
}

int check_valid(long next, long *precursors) {
	int lo = 0, hi = PRECURSORS_LEN - 1, sum;

	while (lo < hi) {
		sum = precursors[lo] + precursors[hi];
		if (sum == next)
		   	return 1;
		else if (sum < next)
			lo++;
		else
			hi--;
	}
	return 0;
}


long find_region(long *seen, int len, long target) {
	int lo = 0, hi = 1, sum;

	sum = seen[lo] + seen[hi];
	while (sum != target) {
		if (sum < target) {
			sum += seen[++hi];
		} else {
			sum -= seen[lo++];
		}
	}
	qsort(&seen[lo], hi - lo + 1, sizeof(long), compar);
	return seen[lo] + seen[hi];
}
