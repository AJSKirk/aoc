#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/hashtable_num.h"

#define NUM_BITS 36  // Gonna need longs
#define LINE_BUFFER 64
#define MEM_TABLE_SIZE 1024 * 4096

struct mask {
	long zero_mask;
	unsigned long x_mask;
};

struct mask process_mask(char *mask_str);
void write_decode_memory(long loc, long float_mask, long to_store, hash_t *mem, int i);

int main(int argc, char *argv[]) {
	char line[LINE_BUFFER];
	char *instruction, *value, *next_row;
	struct mask current_mask;
	long loc;
	long to_store;
	hash_t *h = hash_new(MEM_TABLE_SIZE);
	hash_t *h2 = hash_new(MEM_TABLE_SIZE);

	for (next_row=fgets(line, LINE_BUFFER, stdin); next_row != NULL;
			next_row=fgets(line, LINE_BUFFER, stdin)) {
		if (line[0] == '\n') break;
		instruction = strtok(line, " [");
		if (strncmp(instruction, "mask", 4) == 0) {
			strtok(NULL, " ");  // Tiny memory leak here
			value = strtok(NULL,  "\n");
			current_mask = process_mask(value);
		} else {
			loc = strtol(strtok(NULL, "]"), NULL, 10);
			strtok(NULL, " ");  // Tiny memory leak here
			to_store = strtol(strtok(NULL, "\n"), NULL, 10); 
			// Write to 2 first before to_store is bitmasked
			write_decode_memory(loc | current_mask.zero_mask, current_mask.x_mask, to_store, h2, 0);
			to_store = current_mask.zero_mask | (to_store & current_mask.x_mask);
			hash_insert(h, loc, to_store);
		}
	}

	printf("Total Memory Value: %lld\n", sum_values(h));
	printf("Total Memory Value with Memory Decoding: %lld\n", sum_values(h2));

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

void write_decode_memory(long loc, long float_mask, long to_store, hash_t *mem, int i) {
	if (i == NUM_BITS || float_mask >> i == 0L) {
		hash_insert(mem, loc, to_store);
		return;
	}
	for (;i<=NUM_BITS; i++) {
		if (1L & (float_mask >> i)) {
			write_decode_memory(loc & ~(1L << i), float_mask, to_store, mem, i + 1);
			write_decode_memory(loc | (1L << i), float_mask, to_store, mem, i + 1);
			break; // Prevent double writes in the same stack level
		}
	}
}

