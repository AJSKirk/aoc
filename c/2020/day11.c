#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEIGHT 128
#define MAX_WIDTH 128

enum states {FREE = 'L', OCCUPIED = '#', FLOOR = '.', HALO = 'H'};

int step(char seats[][MAX_WIDTH], int height, int width, int thresh,
		int (*neighbour_func)(char [][MAX_WIDTH], int, int));
int count_occupied(char seats[][MAX_WIDTH], int height, int width);
int count_adjacent(char seats[][MAX_WIDTH], int row, int col);
int count_visible(char seats[][MAX_WIDTH], int row, int col);

int main(int argc, char* argv[]) {
	int height, width, col;
	char seats[MAX_HEIGHT][MAX_WIDTH];
	char vis_seats[MAX_HEIGHT][MAX_WIDTH];
	char c;
	
	for (col=0; col<MAX_WIDTH; col++)
		seats[0][col] = HALO;  // Top halo

	seats[1][0] = HALO;
	col = 1;
	height = 1;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			seats[height][col++] = HALO;  // Right halo
			width = col;
			col = 0;
			height++;
			seats[height][col++] = HALO;  // Left halo
			continue;
		} else {
			seats[height][col++] = c;
		}
	}
	
	for (col=0; col<MAX_WIDTH; col++) {
		seats[height][col] = HALO;  // Bottom halo
	}
	height++;

	memcpy(vis_seats, seats, MAX_HEIGHT * MAX_WIDTH * sizeof(char));

	do {
		;
	} while (step(seats, height, width, 4, &count_adjacent) != 0);

	do {
		;
	} while (step(vis_seats, height, width, 5, &count_visible) != 0);

	printf("Occupied Seats under Adjacency Rule: %d\n", count_occupied(seats, height, width));
	printf("Occupied Seats under Visibility Rule: %d\n", count_occupied(vis_seats, height, width));

	return 0;
}

int step(char seats[][MAX_WIDTH], int height, int width, int thresh, 
		int (*neighbour_func)(char [][MAX_WIDTH], int, int)) {
	int row, col, delta = 0, neighbours;
	int next[height + 1][width];
	int nrow, ncol;

	for (row=1; row<height-1; row++) {
		for (col=1; col<width-1; col++) {
			if (seats[row][col] == FREE && neighbour_func(seats, row, col) == 0) {
				next[row][col] = OCCUPIED;
				delta++;
			} else if (seats[row][col] == OCCUPIED && neighbour_func(seats, row, col) >= thresh) {
				next[row][col] = FREE;
				delta++;
			} else {
				next[row][col] = seats[row][col];
			}
		}
	}

	for (row=1; row<height-1; row++) {
		for (col=1; col<width-1; col++) {
			seats[row][col] = next[row][col];
		}
	} 

	return delta;
}

int count_occupied(char seats[][MAX_WIDTH], int height, int width) {
	int count = 0, row, col;

	for (row=0; row<height; row++) {
		for (col=0; col<width; col++) {
			if (seats[row][col] == OCCUPIED)
				count++;
		}
	}
	return count;
}

int count_adjacent(char seats[][MAX_WIDTH], int row, int col) {
	int neighbours = 0;
	int nrow, ncol;

	for (nrow=row-1; nrow<=row+1; nrow++)
		for (ncol=col-1; ncol<=col+1; ncol++)
			if (nrow != row || ncol != col)
				neighbours += seats[nrow][ncol] == '#';

	return neighbours;
}

int count_visible(char seats[][MAX_WIDTH], int row, int col) {
	int row_dir, col_dir;
	int visible = 0;
	int nrow, ncol;

	for (row_dir=-1; row_dir <= 1; row_dir++) { // -1, 0, 1
		for (col_dir=-1; col_dir <= 1; col_dir++) {
			if (row_dir == 0 && col_dir == 0)  // Avoid infinite loop
				continue;
			nrow = row;
			ncol = col;
			while (seats[nrow][ncol] != HALO && ((nrow == row && ncol == col) || seats[nrow][ncol] != FREE)) {
				if ((nrow != row || ncol != col) && seats[nrow][ncol] == OCCUPIED) {
					visible++;
					break;
				}
				nrow += row_dir;
				ncol += col_dir;
			}
		}
	}
	return visible;
}
