#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable_ptr.h"

#define KEY_BUFFER 32

hash_t *hash_new(int size) {
	hash_t *h = calloc(1, sizeof(hash_t));
	h->size = size;
	h->keys = calloc(size, sizeof(long));
	h->values = calloc(size, sizeof(void *));
	return h;
}

long hash(long x) {
	// Magic from StackOverflow
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

void hash_insert(hash_t *h, long key, void *val) {
	int i = hash_index(h, key);
	h->values[i]  = val;
	h->keys[i] = key;
}

void *hash_lookup(hash_t *h, long key) {
	int i = hash_index(h, key);
	return h->values[i];
}
