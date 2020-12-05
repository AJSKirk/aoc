#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define NUM_SEATS 1024 // 128 * 8

int find_element(char* pass, int len);

int main(int argc, char* argv[]) {
	char rowstrings[NUM_SEATS][8], colstrings[NUM_SEATS][4];
	int row, col, id,  largest_id = 0;
	bool seats[NUM_SEATS] = {false};
	int i = 0, num_tickets = 0, my_id;

	
	// Need to read in stream first before allocating to threads
	while (scanf("%7s%3s\n", rowstrings[i], colstrings[i]) > 0) {
		i++;
	}

	num_tickets = i; // Will be less than the number of seats

	# pragma omp parallel\
	shared(num_tickets, seats, rowstrings, colstrings, my_id) \
   	private(i, row, col, id) default(none) \
	reduction(max:largest_id)
	{
		if (omp_get_thread_num() == 0) printf("Running on %d threads\n", omp_get_num_threads());

		#pragma omp for schedule(static)
		for (i=0; i<num_tickets; i++) {
			row = find_element(rowstrings[i], 7);
			col = find_element(colstrings[i], 3);
			id = row * 8 + col;
			seats[id] = true;
			if (id > largest_id) largest_id = id;
		}

		#pragma omp for schedule(static)
		for (i=1; i<NUM_SEATS; i++) {
			if (seats[i] == false && seats[i-1] && seats[i+1]) my_id = i; // Real risk of race condition here
		}
	}

	printf("The largest Ticket ID is: %d\n", largest_id);
	printf("My Ticket ID is: %d\n", my_id);
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
