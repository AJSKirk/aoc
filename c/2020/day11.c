#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEIGHT 128
#define MAX_WIDTH 128

//enum states {EMPTY: 0, OCCUPIED: 1, NOSEAT: 0};

int step(char seats[][MAX_WIDTH], int height, int width);
int count_occupied(char seats[][MAX_WIDTH], int height, int width);
int count_neighbours(char seats[][MAX_WIDTH], int height, int width, int row, int col);

int main(int argc, char* argv[]) {
	int height=0, width=0, col=0;
	char seats[MAX_HEIGHT][MAX_WIDTH];
	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			width = col;
			col = 0;
			height++;
			continue;
		} else {
			seats[height][col++] = c;
		}
	}
	

	do {
		;
	} while (step(seats, height, width) != 0);


	printf("%d\n", count_occupied(seats, height, width));

	return 0;
}

int step(char seats[][MAX_WIDTH], int height, int width) {
	int row, col, delta = 0, neighbours;
	int next[height][width];
	int nrow, ncol;

	for (row=0; row<height; row++) {
		for (col=0; col<width; col++) {
			neighbours = count_neighbours(seats, height, width, row, col);
			if (seats[row][col] == 'L' && neighbours == 0) {
				next[row][col] = '#';
				delta++;
			} else if (seats[row][col] == '#' && neighbours >= 4) {
				next[row][col] = 'L';
				delta++;
			} else {
				next[row][col] = seats[row][col];
			}
		}
	}

	for (row=0; row<height; row++) {
		for (col=0; col<width; col++) {
			seats[row][col] = next[row][col];
		}
	}
	return delta;
}

int count_occupied(char seats[][MAX_WIDTH], int height, int width) {
	int count = 0, row, col;

	for (row=0; row<height; row++) {
		for (col=0; col<height; col++) {
			if (seats[row][col] == '#')
				count++;
		}
	}
	return count;
}

int count_neighbours(char seats[][MAX_WIDTH], int height, int width, int row, int col) {
	int neighbours = 0;
	int nrow, ncol;

	for (nrow = row - (row != 0); nrow <= row + (row != height - 1); nrow++) {
		for (ncol = col - (col != 0); ncol <= col + (col != width - 1); ncol++) {
			if (nrow != row || ncol != col) {
				neighbours += seats[nrow][ncol] == '#';
			}
		}
	}

	return neighbours;
}
