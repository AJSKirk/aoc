#include <stdio.h>
#include <stdlib.h>

#define STACK_HEIGHT 8

long execute(char op, long left, long right);

int main(int argc, char *argv[]) {
	long local_total = 0, global_total = 0;
	long total_stack[STACK_HEIGHT], stack_cursor = 0;
	char op_stack[STACK_HEIGHT];
	char c, op = '+';

	while ((c = getchar()) != EOF) switch (c) {
		case ' ':
			break;
		case '\n':
			global_total += local_total;
			local_total = 0;
			op = '+';
			stack_cursor = 0;
			break;
		case '(':
			op_stack[stack_cursor] = op;
			total_stack[stack_cursor++] = local_total;  // Push previous total
			local_total = 0;
			op = '+';
			break;
		case  ')':
			op = op_stack[--stack_cursor];
			local_total = execute(op, total_stack[stack_cursor], local_total);
			break;
		case '+':
		case '*':
			op = c;
			break;
		default:  // Number
			local_total = execute(op, local_total, atoi(&c));
	}
	printf("%ld\n", global_total);

	return 0;
}

long execute(char op, long left, long right) {
	switch (op) {
		case '+':
			return left + right;
		case '*':
			return left * right;
		default:
			printf("Invalid operation: %c\n", op);
	}
	return 0;

}
