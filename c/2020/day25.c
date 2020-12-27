#include <stdio.h>
#include <stdlib.h>

#define DIVISOR 20201227L
#define SUBJECT_NUM 7L
#define NUM_KEYS 2

static inline long step(long x, long y) {return (x * y) % DIVISOR;}

int crack_loop_size(int public_key);

int main(int argc, char *argv[]) {
	int loops[NUM_KEYS], public_keys[NUM_KEYS];
	int i = 0, j;
	int current, subject;

	while (scanf("%d\n", &public_keys[i]) > 0) {
		loops[i] = crack_loop_size(public_keys[i]);
		i++;
	}

	for (i=0; i<NUM_KEYS; i++) { // Run on both as a check
		subject = public_keys[(i + 1) % NUM_KEYS];
		current = 1;
		for (j=0; j<loops[i]; j++)
			current = step(current, subject);
		printf("%d\n", current);
	}

	return 0;
}

int crack_loop_size(int public_key) {
	int size = 0;
	int current = 1;
	while (current != public_key) {
		current = step(current, SUBJECT_NUM);
		size++;
	}
	return size;
}
