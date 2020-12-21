#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_BUFFER 16
#define LINE_BUFFER 512
#define MAX_FOODS 64
#define MAX_INGREDIENTS 64
#define MAX_ALLERGENS 8

struct food {
	char ingredients[MAX_INGREDIENTS][WORD_BUFFER];
	char allergens[MAX_ALLERGENS][WORD_BUFFER];
};

struct food foods[MAX_FOODS];

int main(int argc, char *argv[]) {
	char line[LINE_BUFFER], *next_line;
	char *word;
	int i, j;

	i = 0;
	for (next_line=fgets(line, LINE_BUFFER, stdin); next_line != NULL; next_line=fgets(line, LINE_BUFFER, stdin)) {
		j = 0;
		for (word=strtok(line, " "); word[0]!='('; word=strtok(NULL, " ")) {
			strncpy(foods[i].ingredients[j++], word, WORD_BUFFER);
		}
		j = 0;
		for (word=strtok(NULL, " )\n"); word!=NULL; word=strtok(NULL, " )\n")) {
			strncpy(foods[i].allergens[j++], word, WORD_BUFFER);
		}
		i++;
	}

	printf("X\n");

	return 0;
}
