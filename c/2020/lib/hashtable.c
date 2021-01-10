#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define KEY_BUFFER 32

typedef struct {
	int size;
	char **keys;
	char **values;
} hash_t;

hash_t *hash_new(int size) {
	hash_t *h = calloc(1, sizeof(hash_t));
	h->size = size;
	h->keys = calloc(size, sizeof(char *));
	h->values = calloc(size, sizeof(char *));
	return h;
}

unsigned long hash(char *str) {
	// DJB2 Hash function by Dan Bernstein
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

int hash_index(hash_t *h, char *key) {
	// Index with 1-forward probing
	int i = hash(key) % h->size; 

	while (h->keys[i]) {
		if (strncmp(h->keys[i], key, KEY_BUFFER) == 0) {
			return i;
		}
		i = (i + 1) % h->size;
	}
	return i;
}

void hash_insert(hash_t *h, char *key, char *val) {
	int i = hash_index(h, key);
	h->values[i] = (char *) malloc(KEY_BUFFER * sizeof(char));
	h->keys[i] = (char *) malloc(KEY_BUFFER * sizeof(char));
	strncpy(h->values[i], val, KEY_BUFFER);
	strncpy(h->keys[i], key, KEY_BUFFER);
}

char *hash_lookup(hash_t *h, char *key) {
	int i = hash_index(h, key);
	return h->values[i];  // Calloced, so will be NULL if no hit
}

void free_hash(hash_t *h) {
	free(h->keys);
	free(h->values);
	free(h);
}
