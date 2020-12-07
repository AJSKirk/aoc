#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <judy.h>

#define TARGET_BAG "shinygold"
#define MAX_BAGS 1024
#define BAG_BUFFER 32

struct child_bag {
	int num;
	char *name;
};

int main(int argc, char* argv[]) {
	char row[256], *next_row;
	char *parent_name, *next_child_name, *word;
	char *target_container = parent_name;
	struct child_bag next_child;
	
	Pvoid_t bags = (Pvoid_t) NULL;
	PWord_t *value_ptr;

	do {
		next_row = fgets(row, 256, stdin);
		parent_name = (char *) calloc(BAG_BUFFER, sizeof(char));
		for (word=strtok(row, " ,.\n"); word; word=strtok(NULL, " ,.\n")) {
			//printf("%s\n", word);
			if (strncmp(word, "contain", 32) == 0 || strncmp(word, "bag", 3) == 0) {
				if (strnlen(next_child_name, 3) >= 3) {
					JLI(value_ptr, bags, *next_child_name);
					*value_ptr = (PWord_t) parent_name;
				}
				next_child_name = (char *) calloc(BAG_BUFFER, sizeof(char));
				target_container = next_child_name;
			} else if (isdigit(*word)) {
				next_child.num = atoi(word);
			}
			else {
				strncat(target_container, word, 32);
				//strncat(target_container, " ", 32);
			}
		}
	} while (next_row != NULL);

	/* Test Array Iteration*/
	uint8_t idx[MAX_BAGS];
	JSLF(value_ptr, bags, idx);
	while (value_ptr != NULL) {
		printf("%s -> %s", idx, (char *) value_ptr);
	}

	JudySLFreeArray(&bags, PJE0);
}

