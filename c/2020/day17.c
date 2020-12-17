#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define X_MAX 24  // Initial 8 plus space to propagate
#define Y_MAX 24
#define Z_MAX 24
#define SEED_WIDTH 8
#define SEED_HEIGHT 8
#define NSTEPS 6

enum states {ACTIVE = '#', INACTIVE = '.'};

void step(char cubes[Z_MAX][Y_MAX][X_MAX]);
int count_active(char cubes[Z_MAX][Y_MAX][X_MAX]);
void zero_cubes(char cubes[Z_MAX][Y_MAX][X_MAX]);
int count_adjacent(char cubes[Z_MAX][Y_MAX][X_MAX], int z, int y, int x);

int main(int argc, char* argv[]) {
	char cubes[Z_MAX][Y_MAX][X_MAX];
	char c;
	int z = Z_MAX / 2;
	int y = Y_MAX / 2 - SEED_HEIGHT / 2;
	int x = X_MAX / 2 - SEED_WIDTH / 2;
	int i;

	zero_cubes(cubes);
	
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			y++;
			x = X_MAX / 2 - SEED_WIDTH / 2;
		} else {
			cubes[z][y][x++] = c;
		}
	}


	for (i=0; i<NSTEPS; i++) {
		step(cubes);
	}
	
	printf("Active Cubes after Boot: %d\n", count_active(cubes));

	return 0;
}

void step(char cubes[Z_MAX][Y_MAX][X_MAX]) {
	int x, y, z, neighbours;
	static char next[Z_MAX][Y_MAX][X_MAX];

	zero_cubes(next);

	for (z=1; z<Z_MAX-1;z++) 
		for (y=1; y<Y_MAX-1; y++) 
			for (x=1; x<X_MAX-1; x++)  {
				neighbours = count_adjacent(cubes, z, y, x);
				if (cubes[z][y][x] == ACTIVE && (neighbours < 2 || neighbours > 3))
					next[z][y][x] = INACTIVE;
				else if (cubes[z][y][x] == INACTIVE && neighbours == 3)
					next[z][y][x] = ACTIVE;
				else
					next[z][y][x] = cubes[z][y][x];
			}

	memcpy(cubes, next, Z_MAX * Y_MAX * X_MAX);
}

void zero_cubes(char cubes[Z_MAX][Y_MAX][X_MAX]) {
	int x, y, z;

	for (z=0; z<Z_MAX;z++) 
		for (y=0; y<Y_MAX; y++) 
			for (x=0; x<X_MAX; x++) 
				cubes[z][y][x] = INACTIVE;
}

int count_active(char cubes[Z_MAX][Y_MAX][X_MAX]) {
	int count = 0, x, y, z;

	for (z=0; z<Z_MAX;z++) 
		for (y=0; y<Y_MAX; y++) 
			for (x=0; x<X_MAX; x++) 
				if (cubes[z][y][x] == ACTIVE)
					count++;
	return count;
}

int count_adjacent(char cubes[Z_MAX][Y_MAX][X_MAX], int z, int y, int x) {
	int neighbours = 0;
	int nx, ny, nz;

	for (nz=z-1; nz<=z+1; nz++)
		for (ny=y-1; ny<=y+1; ny++)
			for (nx=x-1; nx<=x+1; nx++)
				if (nz != z || ny != y || nx != x)
					neighbours += cubes[nz][ny][nx] == ACTIVE;

	return neighbours;

}
