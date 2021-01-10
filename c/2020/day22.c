#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "lib/double_linked_list.h"
#include "lib/hashtable.h"

#define NUM_PLAYERS 2
#define MAX_DIGITS 2  // Max digits in card values
#define HISTORY_SIZE 2048 * 4

int combat_game(struct list_meta **decks);
int combat_round(int *cards);
void push_cards(struct list_meta **decks, int *cards, int winner);
int recursive_combat_game(struct list_meta **decks);
int smallest_deck(struct list_meta **decks);
int score(struct list_meta *win_deck);
char *deck_to_str(struct list_meta *deck);

int main(int argc, char *argv[]) {
	struct list_meta *decks[NUM_PLAYERS];
	int card, i, winner;
	char row[32];

	for (i=0; i<NUM_PLAYERS; i++) {
		decks[i] = list_create();
		fgets(row, 32, stdin);  // Clear player name
		while (scanf("%d", &card) > 0) {
			push_tail(decks[i], card);
		}
	}

	winner = recursive_combat_game(decks);

	// Winner of the game must be the winner of the last round
	printf("%d\n", score(decks[winner]));

	return 0;
}

int score(struct list_meta *win_deck) {
	int i, score = 0;
	int *win_cards = to_array(win_deck);

	for (i=0; i<win_deck->length; i++)
		score += win_cards[i] * (win_deck->length - i);

	free(win_cards);
	return score;
}

int combat_game(struct list_meta **decks) {
	int cards[NUM_PLAYERS];
	int winner, i;

	while (smallest_deck(decks) > 0) {
		for (i=0; i<NUM_PLAYERS; i++) {
			cards[i] = pop_head(decks[i]);
		}
		winner = combat_round(cards);
		push_cards(decks, cards, winner);
	}

	return winner;  // Winner of the game must be winner of the last round
}

void push_cards(struct list_meta **decks, int *cards, int winner) {
	int loser = (winner == 1) ? 0 : 1;  // Only works in 2-player
	push_tail(decks[winner], cards[winner]);
	push_tail(decks[winner], cards[loser]);
}


int combat_round(int *cards) {
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

int recursive_combat_game(struct list_meta **decks) {
	struct list_meta *sub_decks[NUM_PLAYERS];
	int cards[NUM_PLAYERS];
	int winner, i;
	bool subgame, loop;
	char *deck_str;
	hash_t *seen[NUM_PLAYERS];

	for (i=0; i<NUM_PLAYERS; i++)
		seen[i] = hash_new(HISTORY_SIZE);

	while (smallest_deck(decks) > 0) {
		subgame = true;
		loop = true;
		for (i=0; i<NUM_PLAYERS; i++) {
			deck_str = deck_to_str(decks[i]);
			loop &= (hash_lookup(seen[i], deck_str) != NULL);
			hash_insert(seen[i], deck_str, "1");
			free(deck_str);

			cards[i] = pop_head(decks[i]);
			subgame &= (decks[i]->length >= cards[i]);
		}
		if (loop) {
			for (i=0; i<NUM_PLAYERS; i++)
				free_hash(seen[i]);
			return 0;  // Player 1 wins looped games
		} else if (subgame) {
			for (i=0; i<NUM_PLAYERS; i++) {
				sub_decks[i] = copy_list(decks[i], cards[i]);
			}

			winner = recursive_combat_game(sub_decks);

			// Free decks *after* subgame returns (putting it before the return means we can't score the root game)
			for (i=0; i<NUM_PLAYERS; i++)
				free_deck(sub_decks[i]);
		} else {
			winner = combat_round(cards);
		}
		push_cards(decks, cards, winner);
	}
	
	for (i=0; i<NUM_PLAYERS; i++)
		free_hash(seen[i]);
	return winner;
}


char *deck_to_str(struct list_meta *deck) { // Allows us to use string hash tables for previously seen
	char *out;
	int i, cursor = 0;
	int *cards;

	cards = to_array(deck);
	out = (char *) malloc((deck->length * (MAX_DIGITS + 1) + 1) * sizeof(char));  // Add 1 for terminator

	for (i=0; i<deck->length; i++) {
		cursor += sprintf(&out[cursor], "%d,", cards[i]);
	}
	out[cursor] = '\0';
	free(cards);
	return out;
}
