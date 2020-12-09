#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
	printf("Weakness: %ld\n", find_region(seen, i, next));
	return 0;
}

void replace_precursor(long expired, long new, long sorted[]) {
	// We know the list is sorted so we can binary search
	int lo, hi, mid;
	lo = 0;
	hi = PRECURSORS_LEN - 1;

	while (lo <= hi) {
		mid = (lo + hi) / 2;
		if (sorted[mid] < expired) {
			lo = mid + 1;
		} else if (sorted[mid] > expired) {
			hi = mid - 1;
		} else {
			sorted[mid] = new;
			return;
		}
	}
	printf("Search for element %ld failed\n", expired);
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
