#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int size;
	void **keys;
	void ***values;
} hash_t;

hash_t *hash_new(int size) {
	hash_t *h = calloc(1, sizeof(hash_t));
	h->size = size;
	h->keys = calloc(size, sizeof(void *));
	h->values = calloc(size, sizeof(void *));
	return h;
}

int hash_index(hash_t *h, void *key, bool *first) {
	int i = (int) key % h->size; // Trivially simply hash
	while (h->keys[i]) {
		if (h->keys[i] == key) {
			*first = false;
			return i;
		}
		i = (i + i) % h->size;
	}
	*first = true;
	return i;
}

void hash_insert(hash_t *h, void *key, void *val, int allowed_vals) {
	bool first;
	int i = hash_index(h, key, &first), j = 0;
	if (first) {
		h->values[i] = (void **) calloc(allowed_vals, sizeof(char *));
		h->values[i][0] = val;
	} else {
		while (h->values[i][j] != '\0') {
			j++;
		}
		h->values[i][j] = val;
	}
}

void *hash_lookup(hash_t *h, void *key) {
	bool first;
	return h->values[hash_index(h, key, &first)];
}

