#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CLAUSES 4
#define ROOT_BRANCHES 2
#define MAX_BRANCHES 16
#define MAX_RULES 128
#define ROW_BUFFER 128

struct rule {
	int nclauses;
	int clauses[ROOT_BRANCHES][MAX_CLAUSES];  // Each -1 terminated
	char character;
};

struct rule e_rules[MAX_RULES];  // External rules array

int *check(struct rule r, char *str, int len);
int *distinct(int *arr, int max_members);

int main(int argc, char *argv[]) {
	char row[ROW_BUFFER];
	char *next;
	int *paths;
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
		paths = check(e_rules[0], row, strnlen(row, ROW_BUFFER) - 1);
		for (i=0; paths[i] != -1; i++) {
			if (row[paths[i]] == '\n') {
				passing++;
				break;
			}
		}
		free(paths);
	}

	printf("%d\n", passing);

	return 0;
}

int *check(struct rule r, char *str, int len) {
	// Returns remaining to be matched, NULL if rule fails
	int i, j, k, l;
	bool passed = false;

	int *result, *subpaths, *next;
	int **paths;
	int increment;
	int next_cursor;

	if (len <= 0 || str[0] == '\0') {
		result = (int *) malloc(1 * sizeof(int));
		*result = -1;
		return result;
	}

	if (r.nclauses == 0) {
		result = (int *) calloc(2, sizeof(int));
		result[0] = (r.character == *str) ? 1 : -1;
		result[1] = -1;
		return result;
	}

	paths = (int **) malloc(r.nclauses * sizeof(int *));

	for (i=0; i<r.nclauses; i++) {
		paths[i] = (int *) calloc(MAX_BRANCHES, sizeof(int));
		paths[i][1] = -1;

		for (j=0; r.clauses[i][j] != -1; j++) {
			next = (int *) calloc(MAX_BRANCHES, sizeof(int));
			next[0] = -1;
			next_cursor = 0;
			for (k=0; paths[i][k] != -1; k++) {
				increment = paths[i][k];
				if (increment != -1) {
					subpaths = check(e_rules[r.clauses[i][j]], &str[increment], len - increment);
					subpaths = distinct(subpaths, MAX_BRANCHES);
					for (l=0; subpaths[l] != -1; l++)
						next[next_cursor++] = increment + subpaths[l];
					next[next_cursor] = -1;
					free(subpaths);
				}
			}
			next = distinct(next, MAX_BRANCHES);
			for (k=0; next[k] != -1; k++)
				paths[i][k] = next[k];
			paths[i][k] = -1;
			free(next);
		}
	}

	result = (int *) malloc(r.nclauses * MAX_BRANCHES * sizeof(int));
	next_cursor = 0;
	for (i=0; i<r.nclauses; i++) {
		j = 0;
		for (j=0; paths[i][j] != -1; j++)
			result[next_cursor++] = paths[i][j];
		free(paths[i]);
	}
	free(paths);
	result[next_cursor] = -1;
	return result;
}

void set_bit(unsigned int *arr, int k) {
	arr[k / (sizeof(int) * 8)] |= 1 << (k % (sizeof(int) * 8));
}

bool check_bit(unsigned int *arr, int k) {
	return arr[k / (sizeof(int) * 8)] & (1 << k % (sizeof(int) * 8));
}

int *distinct(int *arr, int max_members) {
	unsigned int *seen = calloc(max_members / (sizeof(int) * 8), sizeof(int));

	int i, cursor = 0;
	int *result = malloc(max_members * sizeof(int));


	for (i=0; i<max_members && arr[i] != -1; i++)
		if (!check_bit(seen, arr[i])) {
			set_bit(seen, arr[i]);
			result[cursor++] = arr[i];
		}

	result[cursor] = -1;
	free(arr);
	free(seen);
	return result;
}
