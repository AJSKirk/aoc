#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binary_tree.h"

#define PROGRAM_BUFFER 1024 // 128 * 8

typedef enum {acc, jmp, nop} opcode;

struct operation {
	opcode op;
	int arg;
};

unsigned int parse_opcode(char *op_text);
int execute(struct operation, int *acc);
int simulation_check(struct operation *stack, int terminator);
int brute_force(struct operation *stack, int terminator);
void switch_ops(struct operation *op);

int main(int argc, char* argv[]) {
	struct operation stack[PROGRAM_BUFFER];
	char op_text[4];
	int cursor = 0, accumulator = 0, terminator;
	struct node *root;
	
	while (scanf("%3s %d\n", op_text, &stack[cursor].arg) > 0) {
		stack[cursor].op = parse_opcode(op_text);
		cursor++;
	}

	terminator = cursor;

	cursor = 0;
	root = new_node(0);
	while (1) {
		cursor += execute(stack[cursor], &accumulator);
		if (search(root, cursor) != NULL)
			break;
		insert(root, cursor);
	}

	printf("%d\n", accumulator);

	accumulator = brute_force(stack, terminator);
	printf("%d\n", accumulator);
	
	return 0;
}

unsigned int parse_opcode(char *op_text) {
	opcode op;
	if (strncmp(op_text, "acc", 3) == 0) return acc;
	else if (strncmp(op_text, "jmp", 3) == 0) return jmp;
	else if (strncmp(op_text, "nop", 3) == 0) return nop;

	printf("INVALID OPERATION: %s\n", op_text);
	exit(EXIT_FAILURE);
}

int execute(struct operation op, int *accumulator) {
	switch (op.op) {
		case acc:
			*accumulator += op.arg;  // No break
		case nop:
			return 1;
			break;
		case jmp:
			return op.arg;
			break;
		default:
			printf("No such instruction %u\n", op.op);
	}
	return 1;
}

int simulation_check(struct operation *stack, int terminator) {
	// Returns final acc if program terminates, -1 if loops
	int cursor = 0, accumulator = 0;
	struct node *root = new_node(0);

	while (cursor != terminator) {
		if (cursor > terminator) return -1;
		cursor += execute(stack[cursor], &accumulator);
		if (search(root, cursor) != NULL) { // Looping
			return -1;
		}
		insert(root, cursor);
	}

	return accumulator;
}

int brute_force(struct operation *stack, int terminator) {
	int i, answer;

	for (i=0; i<terminator; i++) {
		switch_ops(&stack[i]);
		answer = simulation_check(stack, terminator);
		if (answer > 0) break;
		switch_ops(&stack[i]);
	}
	return answer;
}

void switch_ops(struct operation *op) {
	if (op->op == jmp)
		op->op = nop;
	else if (op->op == nop)
		op->op = jmp;
}
