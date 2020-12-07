#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

#define TARGET_BAG "shinygold"
#define MAX_BAGS 1024
#define BAG_BUFFER 32
#define MAX_PARENTS 128
#define MAX_CHILDREN 8

typedef struct {
	int num;
	char *name;
} child_bag;

int count_ancestors(hash_t *bags, char *target, char **seen);
bool check_seen(char *candidate, char **seen);
int count_children(hash_t *bags, char *target);

int main(int argc, char* argv[]) {
	char row[256], *next_row;
	char *parent_name, *next_child_name, *word;
	char *target_container;
	child_bag *next_child;
	int child_cursor = 0;

	hash_t *child_idx_bags = hash_new(MAX_BAGS);
	hash_t *parent_idx_bags = hash_new(MAX_BAGS);

	do {
		next_row = fgets(row, 256, stdin);
		// Don't free these calloced vars, the associative array needs that memory
		parent_name = (char *) calloc(BAG_BUFFER, sizeof(char));
		next_child_name = (char *) calloc(BAG_BUFFER, sizeof(char));
		target_container = parent_name;
		next_child = (child_bag *) calloc(1, sizeof(child_bag));
		next_child->num = 1;
		for (word=strtok(row, " ,.\n"); word; word=strtok(NULL, " ,.\n")) {
			if ((strncmp(word, "contain", 7) == 0) || (strncmp(word, "bag", 3) == 0)) {
				if (strnlen(next_child_name, 3) >= 3) {
					hash_insert(child_idx_bags, next_child_name, parent_name, MAX_PARENTS);
					next_child->name = next_child_name;
					hash_insert(parent_idx_bags, parent_name, next_child, MAX_CHILDREN);
					next_child = (child_bag *) calloc(1, sizeof(child_bag));
				}
				next_child_name = (char *) calloc(BAG_BUFFER, sizeof(char));
				target_container = next_child_name;
			} else if (isdigit(*word)) {
				next_child->num = atoi(word);
			}
			else {
				strncat(target_container, word, 32);
			}
		}
	} while (next_row != NULL);

	char **seen = (char **) calloc(MAX_BAGS, sizeof(char *));
	printf("%d\n", count_ancestors(child_idx_bags, TARGET_BAG, seen));
	printf("%d\n", count_children(parent_idx_bags, TARGET_BAG));
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

int count_children(hash_t *bags, char *target) {
	int count = 0, i;
	child_bag **children;
	if (*target == '\0' || strncmp(target, "noother", BAG_BUFFER) == 0) {
		return -1;
	}
	children = hash_lookup(bags, target);
	for(i=0; children[i] != '\0'; i++) {
		int res = children[i]->num * (1 + count_children(bags, children[i]->name));
		count += res;
	}
	return count;
}
