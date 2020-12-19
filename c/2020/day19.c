#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CLAUSES 4
#define MAX_RULES 128
#define ROW_BUFFER 128

struct rule {
	int nclauses;
	int clauses[2][MAX_CLAUSES];  // Each -1 terminated
	char character;
};

struct rule e_rules[MAX_RULES];  // External rules array

char *check(struct rule r, char *str);

int main(int argc, char *argv[]) {
	char row[ROW_BUFFER];
	char *next, *res;
	int id, i;
	int passing = 0;

	for (fgets(row, ROW_BUFFER, stdin); row[0] != '\n'; fgets(row, ROW_BUFFER, stdin)) {
		// Parse rules

		id = atoi(strtok(row, ":"));
		e_rules[id].nclauses = 1;
		i = 0;
		while ((next = strtok(NULL, " \n")) != NULL) {
			if (next[0] == '"') {
				e_rules[id].character = next[1];
				e_rules[id].nclauses = 0;
				break;
			} else if (next[0] == '|') {
				e_rules[id].clauses[e_rules[id].nclauses - 1][i] = -1;
				e_rules[id].nclauses++;
				i = 0;
			} else {
				e_rules[id].clauses[e_rules[id].nclauses - 1][i++] = atoi(next);
			}
		}
		e_rules[id].clauses[e_rules[id].nclauses - 1][i] = -1;
	}

	for (next=fgets(row, ROW_BUFFER, stdin); next!=NULL; next=fgets(row, ROW_BUFFER, stdin)) {
		res = check(e_rules[0], strtok(row, "\n"));
		if (res != NULL && *res == '\0')
			passing++;
	}

	printf("%d\n", passing);

	return 0;
}

char *check(struct rule r, char *str) {
	// Returns remaining to be matched, NULL if rule fails
	char *working_str;
	int i, j;
	bool passed = false;

	working_str = (char *) malloc(strnlen(str, ROW_BUFFER) * sizeof(char));

	if (r.nclauses == 0)
		return (r.character == *str) ? &str[1] : NULL;

	for (i=0; i<r.nclauses; i++) {
		working_str = (char *) malloc(strnlen(str, ROW_BUFFER) * sizeof(char));
		strncpy(working_str, str, ROW_BUFFER);
		for (j=0; r.clauses[i][j] != -1; j++) {
			working_str = check(e_rules[r.clauses[i][j]], working_str);
			if (working_str == NULL)
				break;
		}
		if (r.clauses[i][j] == -1) {
			passed = true;
			break;
		}
	}

	if (passed)
		return working_str;

	// free(working_str);
	return NULL;
}
