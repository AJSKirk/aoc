#include <stdio.h>
#include <stdlib.h>
#include "lib/double_linked_list.h"

#define TAKE_PER_TURN 3
#define NUM_CUPS 9
#define NUM_MOVES 100

void move(struct list_meta *cups);
int calc_target(int current, struct list_meta *slice);
void print_result(struct list_meta *cups);

int main(int argc, char *argv[]) {
	int next, i;
	struct list_meta *cups = list_create(); 
	while ((next = getchar()) != '\n') {
		push_tail(cups, next - '0');
	}

	for(i=0; i<NUM_MOVES; i++)
		move(cups);

	print_result(cups);
	return 0;
}

void move(struct list_meta *cups) {
	struct list_meta *slice;
	int target;
	slice = slice_after_head(cups, TAKE_PER_TURN);
	target = calc_target(peek_head(cups), slice);
	insert_slice(cups, slice, target);
	cycle_fixed(cups, 1);
}

int calc_target(int current, struct list_meta *slice) {
	int candidate = current - 1;
	int passing;

	do {
		passing = 1;
		if (candidate == 0) {
			passing = 0;
			candidate = NUM_CUPS;
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
	for (i=0; i<NUM_CUPS-1; i++)
		printf("%d", arr_cups[i]);
	printf("\n");
}
