#include <stdio.h>
#include <stdlib.h>

#define STACK_HEIGHT 8

struct frame {
	long total;
	char op;
};

struct frame stack[STACK_HEIGHT];
int stack_cursor = 0;
void push(struct frame);
struct frame pop(void);

long execute(char op, long left, long right);
char peek(FILE *stream);

int main(int argc, char *argv[]) {
	long local_total = 0, global_total = 0;
	char c, op = '+';
	struct frame f;

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
			f.op = op; f.total = local_total;
			push(f);
			local_total = 0;
			op = '+';
			break;
		case  ')':
			f = pop();
			local_total = execute(f.op, f.total, local_total);
			break;
		case '+':
		case '*':
			op = c;
			break;
		default:  // Number
			local_total = execute(op, local_total, c - '0');
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

char peek(FILE *stream) {
	char c;
	while ((c = getc(stream)) == ' ') {;}
	ungetc(c, stream);
	return c;
}

void push(struct frame f) {
	stack[stack_cursor++] = f;
}

struct frame pop(void) {
	return stack[--stack_cursor];
}
