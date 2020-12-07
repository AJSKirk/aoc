#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define KEY_BUFFER 32

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

unsigned long hash(char *str) {
	// DJB2 Hash function by Dan Bernstein
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

int hash_index(hash_t *h, void *key, bool *first) {
	int i = hash(key) % h->size; // Trivially simply hash
	while (h->keys[i]) {
		if (strncmp(h->keys[i], key, KEY_BUFFER) == 0) {
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
	h->keys[i] = key;
}

void *hash_lookup(hash_t *h, void *key) {
	bool first;
	int i = hash_index(h, key, &first);
	return h->values[i];
}

