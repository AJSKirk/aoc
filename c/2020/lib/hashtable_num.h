#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int size;
	long *keys;
	long *values;
} hash_t;

hash_t *hash_new(int size);
long hash(long x);
int hash_index(hash_t *h, long key);
void hash_insert(hash_t *h, long key, long val);
long hash_lookup(hash_t *h, long key);
long long sum_values(hash_t *h);
