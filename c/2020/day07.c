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
	char **parents = (char **) calloc(MAX_PARENTS, sizeof(char *));
	int i = 0;
	parents = hash_lookup(bags, TARGET_BAG);
	while (parents[i] != '\0') {
		printf("%s\n", parents[i]);
		i++;
	}
}

