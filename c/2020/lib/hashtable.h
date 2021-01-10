#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int size;
	char **keys;
	char **values;
} hash_t;

unsigned long hash(char *str);
hash_t *hash_new(int size);
int hash_index(hash_t *h, char *key);
void hash_insert(hash_t *h, char *key, char *val);
char *hash_lookup(hash_t *h, char *key);
void free_hash(hash_t *h);
