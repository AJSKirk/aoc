#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lib/double_linked_list.h"

#define NUM_PLAYERS 2

int determine_winner(int *cards);
int smallest_deck(struct list_meta **decks);

int main(int argc, char *argv[]) {
	struct list_meta *decks[NUM_PLAYERS];
	int card, i, cards[NUM_PLAYERS], winner, loser;
	char row[32];
	int *winner_cards;
	long score = 0;

	for (i=0; i<NUM_PLAYERS; i++) {
		decks[i] = list_create();
		fgets(row, 32, stdin);  // Clear player name
		while (scanf("%d", &card) > 0) {
			push_tail(decks[i], card);
		}
	}

	while (smallest_deck(decks) > 0) {
		for (i=0; i<NUM_PLAYERS; i++)
			cards[i] = pop_head(decks[i]);

		winner = determine_winner(cards);
		loser = (winner == 1) ? 0 : 1;  // Only works in 2-player
		push_tail(decks[winner], cards[winner]);
		push_tail(decks[winner], cards[loser]);
	}

	winner_cards = to_array(decks[winner]);
	for (i=0; i<decks[winner]->length; i++)
		score += winner_cards[i] * (decks[winner]->length - i);

	printf("%ld\n", score);

	return 0;
}

int determine_winner(int *cards) {
	int i, winner, max = INT_MIN;

	for (i=0; i<NUM_PLAYERS; i++) {
		if (cards[i] > max) {
			max = cards[i];
			winner = i;
		}
	}
	return winner;
}

int smallest_deck(struct list_meta **decks) {
	int i, min = INT_MAX;

	for (i=0; i<NUM_PLAYERS; i++) 
		if (decks[i]->length < min)
			min = decks[i]->length;

	return min;
}
