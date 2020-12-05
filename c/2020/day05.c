#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_SEATS 1024 // 128 * 8

int find_element(char* pass, int len);

int main(int argc, char* argv[]) {
	char rowstring[8], colstring[4];
	int row, col, id,  largest_id = 0;
	int seats[NUM_SEATS] = {0};
	int my_id, i;

	while (scanf("%7s%3s\n", rowstring, colstring) > 0) {
		row = find_element(rowstring, 7);
		col = find_element(colstring, 3);
		id = row * 8 + col;
		seats[id] = 1;
		if (id > largest_id) largest_id = id;
	}

	for (i=1; i<NUM_SEATS; i++) {
		if (seats[i] == 0 && seats[i-1] == 1 && seats[i+1] == 1) break; // This could be faster
	}

	printf("The largest Ticket ID is: %d\n", largest_id);
	printf("My Ticket ID is: %d\n", i);
}

int find_element(char* pass,  int len) {
	int lo = 0, hi, i, floor;
	hi = (int) pow(2, len) - 1;

	for (i=0; i<len; i++) {
		floor = (hi + lo) / 2;
		if (pass[i] == 'F' || pass[i] == 'L') hi = floor - 1;
		else if (pass[i] == 'B' || pass[i] == 'R') lo  = floor + 1;
	}
	return lo;
}
