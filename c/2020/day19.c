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

int check(struct rule r, char *str);

int main(int argc, char *argv[]) {
	char row[ROW_BUFFER];
	char *next;
	int increment;
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
		printf("%s", row);
		increment = check(e_rules[0], row);
		if (increment != -1 && row[increment] == '\n')
			passing++;
	}

	printf("%d\n", passing);

	return 0;
}

int check(struct rule r, char *str) {
	// Returns remaining to be matched, NULL if rule fails
	int increment, res;
	int i, j;
	bool passed = false;


	if (r.nclauses == 0)
		return (r.character == *str) ? 1 : -1;

	for (i=0; i<r.nclauses; i++) {
		increment = 0;
		for (j=0; r.clauses[i][j] != -1; j++) {
			res = check(e_rules[r.clauses[i][j]], &str[increment]);
			if (res == -1)
				break;
			else
				increment += res;
		}
		if (r.clauses[i][j] == -1) {
			passed = true;
			break;
		}
	}

	if (passed)
		return increment;

	//free(working_str);
	return -1;
}
