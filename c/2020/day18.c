#include <stdio.h>
#include <stdlib.h>

#define STACK_HEIGHT 16

struct frame {
	long total;
	char op;
};

struct frame stack[STACK_HEIGHT];
int stack_cursor = 0;

long execute(char op, long left, long right);
void push(struct frame);
struct frame pop(void);

int main(int argc, char *argv[]) {
	long global_total = 0, tmp = 0;
	char c;
	struct frame f = {.op = '+', .total = 0};

	push(f);
	push(f);
	while ((c = getchar()) != EOF) switch (c) {
		case ' ':
			break;
		case '\n':
			tmp = f.total;
			f = pop();
			tmp = f.total = execute(f.op, f.total, tmp);
			f = pop();
			f.total = execute(f.op, f.total, tmp);
			global_total += f.total;
			f.op = '+'; f.total = 0;
			stack_cursor = 0;
			push(f);
			push(f);
			break;
		case '(':
			push(f);
			f.op = '+'; f.total = 0;
			push(f);
			push(f);
			break;
		case  ')':
			tmp = f.total;
			f = pop();
			tmp = f.total = execute(f.op, f.total, tmp);
			f = pop();
			tmp = f.total = execute(f.op, f.total, tmp);
			f = pop();
			f.total = execute(f.op, f.total, tmp);
			break;
		case '+':
			tmp = f.total;
			f = pop();
			f.total = execute(f.op, f.total, tmp);
			f.op = c;
			push(f);
			f.op = '+'; f.total = 0;
			break;
		case '*':
			tmp = f.total;
			f = pop();
			tmp = f.total = execute(f.op, f.total, tmp);
			f = pop();
			f.total = execute(f.op, f.total, tmp);
			f.op = c;
			push(f);
			f.op = '+'; f.total = 0;
			push(f);
			break;
		default:  // Number
			f.total = execute(f.op, f.total, c - '0');
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

void push(struct frame f) {
	stack[stack_cursor++] = f;
}

struct frame pop(void) {
	return stack[--stack_cursor];
}
