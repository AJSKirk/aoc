#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_DIM 3
#define ROW_BUFFER 256
#define FLOOR_SIZE 164
#define N_AUTOMATA_STEPS 100

enum directions {E, W, SE, SW, NE, NW};

static int map[FLOOR_SIZE][FLOOR_SIZE][FLOOR_SIZE]; // Initialises to zero

void parse_instruction(char *str);
void step(int loc[N_DIM], enum directions dir);
int count_set(void);
void automata_step(void);
int count_neighbours(int x, int y, int z);

int main(int argc, char *argv[]) {
	char row[ROW_BUFFER];
	int i;

	while (scanf("%255s\n", row) > 0) {
		parse_instruction(row);
	}

	printf("%d\n", count_set());

	for (i=1; i<=N_AUTOMATA_STEPS; i++) {
		automata_step();
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

void automata_step(void) {
	static int next[FLOOR_SIZE][FLOOR_SIZE][FLOOR_SIZE];
	static int first = 1;
	int i, j, k;
	int ns;

	if (first) { // Copy map once, then can save time only tracking changes in future
		memcpy(next, map, FLOOR_SIZE * FLOOR_SIZE * FLOOR_SIZE);
		first = 0;
	}
	
	// 3D Coords actually make this real easy
	for (i=1; i<FLOOR_SIZE-1; i++)  // Given myself enough buffer already
		for (j=1; j<FLOOR_SIZE-1; j++)
			for (k=1; k<FLOOR_SIZE-1; k++) {
				if ((FLOOR_SIZE / 2 + i) + (FLOOR_SIZE / 2 + j) + (FLOOR_SIZE / 2 + k) == 3 * FLOOR_SIZE) {
					ns = count_neighbours(i, j, k);
					if (map[i][j][k] && (ns == 0 || ns > 2)) {
						next[i][j][k] = 0;
					} else if (map[i][j][k] == 0 && ns == 2) {
						next[i][j][k] = 1;
					} else
						next[i][j][k] = map[i][j][k];
				}
			}

	for (i=1; i<FLOOR_SIZE-1; i++)
		for (j=1; j<FLOOR_SIZE-1; j++)
			for (k=1; k<FLOOR_SIZE-1; k++) 
				if ((FLOOR_SIZE / 2 + i) + (FLOOR_SIZE / 2 + j) + (FLOOR_SIZE / 2 + k) == 3 * FLOOR_SIZE)
					map[i][j][k] = next[i][j][k]; // Don't know why memcpy was failing here
}

int count_neighbours(int x, int y, int z) {
	int i, j, k;
	int res = 0;
	
	for (i=-1; i<=1; i++)
		for (j=-1; j<=1; j++)
			for (k=-1; k<=1; k++)
				if (i + j + k == 0 && (i != 0 || j != 0 || k != 0)) {
					res += map[x + i][y + j][z + k];
				}
	return res;
}
