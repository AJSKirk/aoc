#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_HEIGHT 128
#define MAX_WIDTH 128

//enum states {EMPTY: 0, OCCUPIED: 1, NOSEAT: 0};

int step(char seats[][MAX_WIDTH], int height, int width, int thresh,
		int (*neighbour_func)(char [][MAX_WIDTH], int, int, int, int));
int count_occupied(char seats[][MAX_WIDTH], int height, int width);
int count_adjacent(char seats[][MAX_WIDTH], int height, int width, int row, int col);
int count_visible(char seats[][MAX_WIDTH], int height, int width, int row, int col);

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
	} while (step(seats, height, width, 5, &count_visible) != 0);

	printf("%d\n", count_occupied(seats, height, width));

	return 0;
}

int step(char seats[][MAX_WIDTH], int height, int width, int thresh, 
		int (*neighbour_func)(char [][MAX_WIDTH], int, int, int, int)) {
	int row, col, delta = 0, neighbours;
	int next[height][width];
	int nrow, ncol;

	for (row=0; row<height; row++) {
		for (col=0; col<width; col++) {
			if (seats[row][col] == 'L' && neighbour_func(seats, height, width, row, col) == 0) {
				next[row][col] = '#';
				delta++;
			} else if (seats[row][col] == '#' && neighbour_func(seats, height, width, row, col) >= thresh) {
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

int count_adjacent(char seats[][MAX_WIDTH], int height, int width, int row, int col) {
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

int count_visible(char seats[][MAX_WIDTH], int height, int width, int row, int col) {
	int row_dir, col_dir;
	int visible = 0;
	int nrow, ncol;

	for (row_dir=-1; row_dir <= 1; row_dir++) { // -1, 0, 1
		for (col_dir=-1; col_dir <= 1; col_dir++) {
			if (row_dir == 0 && col_dir == 0)
				continue;
			nrow = row;
			ncol = col;
			while (nrow >= 0 && nrow < height && ncol >= 0 && ncol < width) {
				if (nrow == row && ncol == col)
					;
				else if (seats[nrow][ncol] == '#') {
					visible += 1;
					break;
				} else if (seats[nrow][ncol] == 'L')
					break;
				nrow += row_dir;
				ncol += col_dir;
			}
		}
	}
	return visible;
}
