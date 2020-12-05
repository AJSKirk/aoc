#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define NUM_SEATS 1024 // 128 * 8

int find_element(char* pass, int len);

int main(int argc, char* argv[]) {
	char rowstring[8], colstring[4];
	int row, col, id,  largest_id = 0;
	bool seats[NUM_SEATS] = {false};
	int i;

	while (scanf("%7s%3s\n", rowstring, colstring) > 0) {
		row = find_element(rowstring, 7);
		col = find_element(colstring, 3);
		id = row * 8 + col;
		seats[id] = true;
		if (id > largest_id) largest_id = id;
	}

	for (i=1; i<NUM_SEATS; i++) {
		if (seats[i] == false && seats[i-1] && seats[i+1]) break;
	}

	printf("The largest Ticket ID is: %d\n", largest_id);
	printf("My Ticket ID is: %d\n", i); // Loop fallthrough, be careful
}

int find_element(char* pass,  int len) {
	int lo = 0, hi, i, mid;
	hi = (int) pow(2, len) - 1;

	for (i=0; i<len; i++) {
		mid = (hi + lo) / 2;
		if (pass[i] == 'F' || pass[i] == 'L') hi = mid - 1;
		else if (pass[i] == 'B' || pass[i] == 'R') lo  = mid + 1;
	}
	return lo;
}
