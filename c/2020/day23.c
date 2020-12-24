#include <stdio.h>
#include <stdlib.h>
#include "lib/double_linked_list.h"

#define TAKE_PER_TURN 3
#define NUM_CUPS 9
#define NUM_MOVES 100
#define BIG_NUM_CUPS 1000000
#define BIG_NUM_MOVES 10000000


void move(struct list_meta *cups, struct node **lookup, int max_cup);
int calc_target(int current, struct list_meta *slice, int max_cup);
void print_result(struct list_meta *cups);
void complete_big_list(struct list_meta *cups, struct node **lookup);
long long product_labels(struct list_meta *cups);

int main(int argc, char *argv[]) {
	int next, i;
	struct list_meta *cups = list_create(); 
	struct list_meta *big_cups = list_create(); 
	struct node **node_lookup = (struct node **) malloc((NUM_CUPS + 1) * sizeof(struct node *));
	struct node **big_node_lookup = (struct node **) malloc((BIG_NUM_CUPS + 1) * sizeof(struct node *));

	while ((next = getchar()) != '\n') {
		push_tail(cups, next - '0');
		push_tail(big_cups, next - '0');
		node_lookup[next - '0'] = cups->tail;
		big_node_lookup[next - '0'] = big_cups->tail;
	}

	for(i=0; i<NUM_MOVES; i++)
		move(cups, node_lookup, NUM_CUPS);

	complete_big_list(big_cups, big_node_lookup);
	for(i=0; i<BIG_NUM_MOVES; i++) {
		move(big_cups, big_node_lookup, BIG_NUM_CUPS);
	}

	print_result(cups);
	printf("The product of the target labls is: %lld\n", product_labels(big_cups));
	return 0;
}

void move(struct list_meta *cups, struct node **lookup, int max_cup) {
	struct list_meta *slice;
	int target;
	slice = slice_after_head(cups, TAKE_PER_TURN);
	target = calc_target(peek_head(cups), slice, max_cup);
	insert_slice(cups, slice, lookup[target]);
	cycle_fixed(cups, 1);
}

int calc_target(int current, struct list_meta *slice, int max_cup) {
	int candidate = current - 1;
	int passing;

	do {
		passing = 1;
		if (candidate == 0) {
			passing = 0;
			candidate = max_cup;
		}
		if (target_in_list(slice, candidate)) {
			passing = 0;
			candidate--;
		}
	} while (passing == 0);

	return candidate;
}

void print_result(struct list_meta *cups) {
	int i;
	int *arr_cups = malloc(NUM_CUPS * sizeof(int));
	cycle_to_target(cups, 1);
	cycle_fixed(cups, 1);
	arr_cups = to_array(cups);
	printf("The cup sequence is: ");
	for (i=0; i<NUM_CUPS-1; i++)
		printf("%d", arr_cups[i]);
	printf("\n");
}

void complete_big_list(struct list_meta *cups, struct node **lookup) {
	int i;
	for (i=NUM_CUPS+1; i<=BIG_NUM_CUPS; i++) {
		push_tail(cups, i);
		lookup[i] = cups->tail;
	}
}

long long product_labels(struct list_meta *cups) {
	long long product = 1;
	int i;
	cycle_to_target(cups, 1);
	for (i=0; i<=2; i++)
		product *= pop_head(cups);

	return product;
}
