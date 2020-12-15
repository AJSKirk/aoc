#include <stdio.h>
#include <stdlib.h>
#include "lib/hashtable_num.h"

#define HISTORY_SIZE 2048 * 2048
#define DURATION 30000000

int main(int argc, char *argv[]) {
	int i = 1;
	int previous, last_observed;
	hash_t *history = hash_new(HISTORY_SIZE);

	while (scanf("%d,", &previous) > 0) {
		hash_insert(history, previous, i++);
	}
	hash_insert(history, previous, 0);

	// Assumes all starting numbers are distinct
	for (; i<= DURATION; i++) {
		last_observed = hash_lookup(history, previous);
		if (last_observed != 0)
			last_observed = i - 1 - last_observed;

		hash_insert(history, previous, i - 1);
		previous = last_observed;
	}

	printf("%d\n", previous);

	return 0;
}
