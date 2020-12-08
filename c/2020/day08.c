#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binary_tree.h"

#define PROGRAM_BUFFER 1024 // 128 * 8

enum opcode {ACC, JMP, NOP};

struct operation {
	enum opcode op;
	int arg;
};

struct machine {
	int pc; // Program counter
	int accumulator;
};


unsigned int parse_opcode(char *op_text);
void execute(struct operation op, struct machine *vm);
int run_program(struct operation *stack, int terminator);
int brute_force(struct operation *stack, int terminator);
void switch_ops(struct operation *op);
void set_bit(unsigned int *arr, int k);
bool check_bit(unsigned int *arr, int k);

int main(int argc, char* argv[]) {
	struct operation stack[PROGRAM_BUFFER];
	char op_text[4];
	int i = 0, accumulator = 0, terminator;
	struct node *root;
	
	while (scanf("%3s %d\n", op_text, &stack[i].arg) > 0) {
		stack[i].op = parse_opcode(op_text);
		i++;
		
		if (i >= PROGRAM_BUFFER) {
			printf("Program Buffer Overflow\n");
			exit(EXIT_FAILURE);
		}
	}

	terminator = i;

	/*cursor = 0;
	root = new_node(0);
	while (1) {
		cursor += execute(stack[cursor], &accumulator);
		if (search(root, cursor) != NULL)
			break;
		insert(root, cursor);
	}

	printf("%d\n", accumulator);*/

	accumulator = brute_force(stack, terminator);
	printf("%d\n", accumulator);
	
	return 0;
}

unsigned int parse_opcode(char *op_text) {
	enum opcode op;
	if (strncmp(op_text, "acc", 3) == 0) return ACC;
	else if (strncmp(op_text, "jmp", 3) == 0) return JMP;
	else if (strncmp(op_text, "nop", 3) == 0) return NOP;

	printf("INVALID OPERATION: %s\n", op_text);
	exit(EXIT_FAILURE);
}

void execute(struct operation op, struct machine *vm) {
	switch (op.op) {
		case ACC:
			vm->accumulator += op.arg;  // No break
		case NOP:
			vm->pc++;
			break;
		case JMP:
			vm->pc += op.arg;
			break;
		default:
			printf("No such instruction %u\n", op.op);
	}
}

int run_program(struct operation *stack, const int terminator) {
	// Returns final acc if program terminates, -1 if loops
	struct machine vm = {.pc=0, .accumulator=0};
	struct node *root = new_node(0);
	unsigned int seen[PROGRAM_BUFFER / (sizeof(int) * 8)];
	
	//vm = calloc(1, sizeof(struct machine));  // Set PC and accumulator to zero

	while (vm.pc < terminator) {
		execute(stack[vm.pc], &vm);
		if (search(root, vm.pc) != NULL) {
			return -1;
		}
		insert(root, vm.pc);
	}

	return vm.accumulator;
}

int brute_force(struct operation *stack, int terminator) {
	int i, answer;

	for (i=0; i<terminator; i++) {
		switch_ops(&stack[i]);
		answer = run_program(stack, terminator);
		if (answer > 0) {
			return answer;
		}
		switch_ops(&stack[i]);
	}
	return answer;
}

void switch_ops(struct operation *op) {
	if (op->op == JMP)
		op->op = NOP;
	else if (op->op == NOP)
		op->op = JMP;
}

void set_bit(unsigned int *arr, int k) {
	arr[k / (sizeof(int) * 8)] |= 1U << (k % (sizeof(int) * 8));
}

bool check_bit(unsigned int *arr, int k) {
	return arr[k / (sizeof(int) * k)] & (1U << k % (sizeof(int) * 8));
}

