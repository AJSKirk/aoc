#include <stdio.h>
#include <stdlib.h>
#include "lib/double_linked_list.h"

#define NUM_PLAYERS 2

int main(int argc, char *argv[]) {
	struct list_meta *decks[NUM_PLAYERS];
	int card, i;
	char row[32];

	for (i=0; i<NUM_PLAYERS; i++) {
		decks[i] = list_create();
		fgets(row, 32, stdin);  // Clear player name
		while (scanf("%d", &card) > 0) {
			push_tail(decks[i], card);
		}
	}

	return 0;
}
