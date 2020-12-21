#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "lib/hashtable.h"

#define WORD_BUFFER 16
#define LINE_BUFFER 1024
#define MAX_FOODS 128
#define MAX_INGREDIENTS 128
#define MAX_ALLERGENS 8

struct food {
	char ingredients[MAX_INGREDIENTS][WORD_BUFFER];
	char allergens[MAX_ALLERGENS][WORD_BUFFER];
	int n_ingredients;
	int n_allergens;
};

struct food foods[MAX_FOODS];
int num_foods;
hash_t *ingredient_hash;
hash_t *allergen_hash ;

// Function Prototypes
struct food intersection(struct food f1, struct food f2);
int lock_allergen(char *allergen);


int main(int argc, char *argv[]) {
	char line[LINE_BUFFER], *next_line;
	char *word;
	int i, j;
	int delta, n_safe;
	struct food intersect;

	ingredient_hash = hash_new(MAX_FOODS);
	allergen_hash = hash_new(MAX_FOODS);

	i = 0;
	for (next_line=fgets(line, LINE_BUFFER, stdin); next_line!=NULL && line[0]!='\n'; next_line=fgets(line, LINE_BUFFER, stdin)) {
		j = 0;
		for (word=strtok(line, " "); word[0]!='('; word=strtok(NULL, " ")) {
			strncpy(foods[i].ingredients[j++], word, WORD_BUFFER);
		}
		j = 0;
		for (word=strtok(NULL, ", )\n"); word!=NULL; word=strtok(NULL, ", )\n")) {
			strncpy(foods[i].allergens[j++], word, WORD_BUFFER);
		}
		foods[i].n_allergens = j;
		i++;
	}
	num_foods = i;

	do {
		delta = 0;
		for (i=0; i<num_foods; i++) 
			for (j=0; j<foods[i].n_allergens; j++)
				delta += lock_allergen(foods[i].allergens[j]);
	} while (delta > 0);

	n_safe = 0;
	for (i=0; i<num_foods; i++) {
		j = 0;
		while (foods[i].ingredients[j][0] != '\0') {
			if (hash_lookup(ingredient_hash, foods[i].ingredients[j++]) == NULL)
				n_safe++;
		}
	}

	printf("%d\n", n_safe);

	return 0;
}

struct food intersection(struct food f1, struct food f2) {
	// Caching would be nice, but not really worth the overhead here
	struct food res;
	int i = 0, j = 0, k = 0;

	while (f1.ingredients[i][0] != '\0') {
		if (hash_lookup(ingredient_hash, f1.ingredients[i]) != NULL) {
			i++;
			continue;  // Already locked
		}
		j = 0;
		while (f2.ingredients[j][0] != '\0') {
			if (strncmp(f1.ingredients[i], f2.ingredients[j], WORD_BUFFER) == 0) {
				strncpy(res.ingredients[k++], f1.ingredients[i], WORD_BUFFER);
			}
			j++;
		}
		i++;
	}
	res.ingredients[k][0] = '\0';  // I think it's zero-initialised anyway, but just being safe
	res.n_ingredients = k;

	i = j = k = 0;
	while (f1.allergens[i][0] != '\0') {
		if (hash_lookup(allergen_hash, f1.allergens[i]) != NULL) {
			i++;
			continue;
		}
		j = 0;
		while (f2.allergens[j][0] != '\0') {
			if (strncmp(f1.allergens[i], f2.allergens[j], WORD_BUFFER) == 0) {
				strncpy(res.allergens[k++], f1.allergens[i], WORD_BUFFER);
			}
			j++;
		}
		i++;
	}
	res.allergens[k][0] = '\0';
	res.n_allergens = k;

	return res;
}

int lock_allergen(char *allergen) {
	int i, j;
	bool first, contained;
	struct food intersect;
	if (hash_lookup(allergen_hash, allergen))
		return 0;
	first = true;
	for (i=0; i<num_foods; i++) {
		contained = false;
		for (j=0; j<foods[i].n_allergens; j++) 
			if (strncmp(foods[i].allergens[j], allergen, WORD_BUFFER) == 0) {
				contained = true;
				break;
			}

		if (contained) {
			if (first) {
				intersect = intersection(foods[i], foods[i]);
				first = false;
			} else
				intersect = intersection(intersect, foods[i]);
		}
	}

	if (intersect.n_ingredients == 1 && intersect.n_allergens == 1) {
		hash_insert(ingredient_hash, intersect.ingredients[0], intersect.allergens[0]);
		hash_insert(allergen_hash, intersect.allergens[0], intersect.ingredients[0]);
		printf("%s - %s\n", intersect.allergens[0], intersect.ingredients[0]);
		return 1;
	}
	return 0;
}
