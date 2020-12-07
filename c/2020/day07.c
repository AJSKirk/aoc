#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assoc_array.h"

#define TARGET_BAG "shinygold"
#define MAX_BAGS 1024
#define BAG_BUFFER 32
#define MAX_PARENTS 128

struct child_bag {
	int num;
	char *name;
};

int count_ancestors(hash_t *bags, char *target, char **seen);
bool check_seen(char *candidate, char **seen);

int main(int argc, char* argv[]) {
	char row[256], *next_row;
	char *parent_name, *next_child_name, *word;
	char *target_container;
	struct child_bag next_child;

	hash_t *bags = hash_new(MAX_BAGS);

	do {
		next_row = fgets(row, 256, stdin);
		parent_name = (char *) calloc(BAG_BUFFER, sizeof(char));
		next_child_name = (char *) calloc(BAG_BUFFER, sizeof(char));
		target_container = parent_name;
		for (word=strtok(row, " ,.\n"); word; word=strtok(NULL, " ,.\n")) {
			if ((strncmp(word, "contain", 7) == 0) || (strncmp(word, "bag", 3) == 0)) {
				if (strnlen(next_child_name, 3) >= 3) {
					hash_insert(bags, next_child_name, parent_name, MAX_PARENTS);
				}
				next_child_name = (char *) calloc(BAG_BUFFER, sizeof(char));
				target_container = next_child_name;
			} else if (isdigit(*word)) {
				next_child.num = atoi(word);
			}
			else {
				strncat(target_container, word, 32);
			}
		}
	} while (next_row != NULL);

	// Print array
	int i = 0;
	char **seen = (char **) calloc(MAX_BAGS, sizeof(char *));
	printf("%d\n", count_ancestors(bags, TARGET_BAG, seen));
}

int count_ancestors(hash_t *bags, char *target, char **seen) {
	char **parents;
	int count = 0, i = 0;
	
	parents = hash_lookup(bags, target);
	while (parents[i] != '\0') {
		if (check_seen(parents[i], seen)) {
			count += count_ancestors(bags, parents[i], seen);
			count++;
		}
		i++;
	}
	//free(parents); // We can free memory as we go
	return count;
}

bool check_seen(char *candidate, char **seen) {
	// Appends to seen and returns 1 if it wasn't there earlier
	int i=0;
	while (seen[i] != '\0') {
		if (strncmp(seen[i], candidate, BAG_BUFFER) == 0) 
			return false;
		i++;
	}
	seen[i] = candidate;
	return true;
}
