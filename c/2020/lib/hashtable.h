#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int size;
	void **keys;
	void ***values;
} hash_t;

unsigned long hash(char *str);
hash_t *hash_new(int size);
int hash_index(hash_t *h, void *key, bool *first);
void hash_insert(hash_t *h, void *key, void *val, int allowed_vals);
void *hash_lookup(hash_t *h, void *key);
