#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TILE_SIZE 10
#define MAX_TILES 256

struct tile {
	int id;
	char grid[TILE_SIZE][TILE_SIZE];
};

struct tile tiles[MAX_TILES];

int main(int argc, char *argv[]) {
	char line[TILE_SIZE+2], *next;
	int i = 0, j;

	for (next=fgets(line, TILE_SIZE+2, stdin); next!=NULL; next=fgets(line, TILE_SIZE+2, stdin)) {
		if (line[0] == '\n') {
			i++;
			continue;
		} else if (line[0] == 'T') {
			strtok(line, " ");
			tiles[i].id = atoi(strtok(NULL, ":"));
			//printf("%d\n", tiles[i].id);
			j = 0;
		} else {
			strncpy(tiles[i].grid[j++], line, TILE_SIZE);
		}
	}

	return 0;
}
