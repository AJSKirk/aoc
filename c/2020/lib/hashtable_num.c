#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define KEY_BUFFER 32

typedef struct {
	int size;
	long *keys;
	long *values;
} hash_t;

hash_t *hash_new(int size) {
	hash_t *h = calloc(1, sizeof(hash_t));
	h->size = size;
	h->keys = calloc(size, sizeof(long));
	h->values = calloc(size, sizeof(long));
	return h;
}

long hash(long x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

int hash_index(hash_t *h, long key) {
	// Index with 1-forward probing
	int i = hash(key) % h->size;

	while (h->keys[i]) {
		if (h->keys[i] == key) {
			return i;
		}
		i = (i + 1) % h->size;
	}
	return i;
}

void hash_insert(hash_t *h, long key, long val) {
	int i = hash_index(h, key);
	h->values[i]  = val;
	h->keys[i] = key;
}

long hash_lookup(hash_t *h, long key) {
	int i = hash_index(h, key);
	return h->values[i];
}

long long sum_values(hash_t *h) {
	int i;
	long total = 0;
	for (i=0; i<h->size; i++) {
		if (h->values[i] != 0) {
			total += h->values[i];
		}
	}
	return total;
}
