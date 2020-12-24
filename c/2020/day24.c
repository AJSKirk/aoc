#include <stdio.h>
#include <stdlib.h>

#define N_DIM 3
#define ROW_BUFFER 256
#define FLOOR_SIZE 64

enum directions {E, W, SE, SW, NE, NW};

static int map[FLOOR_SIZE][FLOOR_SIZE][FLOOR_SIZE]; // Initialises to zero

void parse_instruction(char *str);
void step(int loc[N_DIM], enum directions dir);
int count_set(void);

int main(int argc, char *argv[]) {
	char row[ROW_BUFFER];

	while (scanf("%255s\n", row) > 0) {
		parse_instruction(row);
	}

	printf("%d\n", count_set());

	return 0;
}

void parse_instruction(char *str) {
	// Strip newline first!
	int i;
	char c;
	int loc[N_DIM] = {0, 0, 0};
	enum directions dir = 0;
	for (i=0; (c=str[i]) != '\0'; i++) {
		switch (c) {
			case 'n':
				dir += NE;
				break;
			case 's':
				dir += SE;
				break;
			case 'e':
				dir += E;
				step(loc, dir);
				dir = 0;
				break;
			case 'w':
				dir += W;
				step(loc, dir);
				dir = 0;
				break;
			default:
				printf("Invalid direction '%c'\n", c);
				exit(EXIT_FAILURE);
		}
	}
	map[FLOOR_SIZE / 2 + loc[0]][FLOOR_SIZE / 2 + loc[1]][FLOOR_SIZE / 2 + loc[2]]++;
	map[FLOOR_SIZE / 2 + loc[0]][FLOOR_SIZE / 2 + loc[1]][FLOOR_SIZE / 2 + loc[2]] %= 2;
}

void step(int loc[N_DIM], enum directions dir) {
	switch (dir) {
		case E:
			loc[0]++;
			loc[1]--;
			break;
		case W:
			loc[0]--;
			loc[1]++;
			break;
		case SE:
			loc[1]--;
			loc[2]++;
			break;
		case SW:
			loc[0]--;
			loc[2]++;
			break;
		case NE:
			loc[0]++;
			loc[2]--;
			break;
		case NW:
			loc[1]++;
			loc[2]--;
			break;
		default:
			printf("Invaid direction '%d'\n", dir);
			exit(EXIT_FAILURE);
	}
}

int count_set(void) {
	int i, j, k;
	int res = 0;
	for (i=0; i<FLOOR_SIZE; i++)
		for (j=0; j<FLOOR_SIZE; j++)
			for (k=0; k<FLOOR_SIZE; k++)
				res += map[i][j][k];
	return res;
}
