#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/hashtable_num.h"

#define NUM_BITS 36  // Gonna need longs
#define LINE_BUFFER 64
#define MEM_TABLE_SIZE 1024

struct mask {
	long zero_mask;
	long x_mask;
};

struct mask process_mask(char *mask_str);

int main(int argc, char *argv[]) {
	char line[LINE_BUFFER];
	char *instruction, *value, *next_row;
	struct mask current_mask;
	int loc;
	long to_store;
	hash_t *h = hash_new(MEM_TABLE_SIZE);

	for (next_row=fgets(line, LINE_BUFFER, stdin); next_row != NULL;
			next_row=fgets(line, LINE_BUFFER, stdin)) {
		if (line[0] == '\n') break;
		instruction = strtok(line, " [");
		if (strncmp(instruction, "mask", 4) == 0) {
			strtok(NULL, " ");  // Tiny memory leak here
			value = strtok(NULL,  "\n");
			current_mask = process_mask(value);
		} else {
			loc = atoi(strtok(NULL, "]"));
			strtok(NULL, " ");  // Tiny memory leak here
			//to_store = strtol(strtok(NULL, "\n"), NULL, 10);
			to_store = atol(strtok(NULL, "\n"));
			to_store = current_mask.zero_mask | (to_store & current_mask.x_mask);
			hash_insert(h, loc, to_store);
		}
	}

	printf("%lld\n", sum_values(h));

	return 0;
}

struct mask process_mask(char *mask_str) {
	int i;
	struct mask result = {0, 0};

	for (i=0;  i<NUM_BITS; i++) {
		if (mask_str[i] == '1')
			result.zero_mask |= 1L << (NUM_BITS - i - 1);
		else if (mask_str[i] == 'X')
			result.x_mask |= 1L << (NUM_BITS - i - 1);
	}

	return result;
}
