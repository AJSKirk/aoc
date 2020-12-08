#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
int run_program(struct operation *stack, int terminator, struct machine *vm);
void switch_ops(struct operation *op);
void set_bit(unsigned int *arr, int k);
bool check_bit(unsigned int *arr, int k);
int backtrace(struct operation *stack, int terminator);

int main(int argc, char* argv[]) {
	struct operation stack[PROGRAM_BUFFER];
	char op_text[4];
	int i = 0, terminator;
	struct machine vm = {.pc = 0, .accumulator = 0};
	
	while (scanf("%3s %d\n", op_text, &stack[i].arg) > 0) {
		stack[i].op = parse_opcode(op_text);
		i++;
		
		if (i >= PROGRAM_BUFFER) {
			printf("Program Buffer Overflow\n");
			exit(EXIT_FAILURE);
		}
	}

	terminator = i;

	run_program(stack, terminator, &vm);
	printf("Register Value at Failure is: %d\n", vm.accumulator);
	printf("Correct Register Value is: %d\n", backtrace(stack, terminator));
	
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

int run_program(struct operation *stack, const int terminator, struct machine *vm) {
	// Returns final acc if program terminates, -1 if loops
	unsigned int seen[PROGRAM_BUFFER / (sizeof(int) * 8)] = {0U};

	memset(vm, 0, sizeof(struct machine)); // Zero registers
	set_bit(seen, 0);
	while (vm->pc < terminator) {
		execute(stack[vm->pc], vm);

		if (check_bit(seen, vm->pc)) {
			return -1;
		}
		set_bit(seen, vm->pc);
	}

	return vm->accumulator;
}

int backtrace(struct operation *stack, int terminator) {
	struct machine vm = {.pc = 0, .accumulator = .0};
	unsigned int targets[PROGRAM_BUFFER / (sizeof(int) * 8)] = {0};
	bool next_target = true, found = false;
	int i, delta = 0;

	// Initialise targets
	set_bit(targets, terminator);
	do {
		delta = 0;
		for (i=terminator-1; i>=0; i--) {
			if (check_bit(targets, i)) 
				continue;
			if (next_target && (stack[i].op == ACC || stack[i].op == NOP)) {
				set_bit(targets, i); // Make this op a target
				delta++;
				next_target = true;
			} else if (stack[i].op == JMP && check_bit(targets, i + stack[i].arg)) {
				set_bit(targets, i);
				delta++;
				next_target = true;
			} else {
				next_target = false;
			}
		}
	} while (delta + 0);

	// Run over and check changes
	while (vm.pc < terminator) {
		if (!found && stack[vm.pc].op == JMP && check_bit(targets, vm.pc + 1)) {
			switch_ops(&stack[vm.pc]);
			found = true;
		}
		if (!found && stack[vm.pc].op == NOP && check_bit(targets, vm.pc + stack[vm.pc].arg)) {
			switch_ops(&stack[vm.pc]);
			found = true;
		}
		execute(stack[vm.pc], &vm);
	}
	
	return vm.accumulator;
}

void switch_ops(struct operation *op) {
	if (op->op == JMP)
		op->op = NOP;
	else if (op->op == NOP)
		op->op = JMP;
}

void set_bit(unsigned int *arr, int k) { // Hella memory unsafe
	arr[k / (sizeof(int) * 8)] |= 1 << (k % (sizeof(int) * 8));
}

bool check_bit(unsigned int *arr, int k) { // Hella memory unsafe
	return arr[k / (sizeof(int) * 8)] & (1 << k % (sizeof(int) * 8));
}

