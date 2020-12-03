#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[]) {
	FILE* fp;
	clock_t start = clock();

	if (argc != 2) {
		printf("Usage: dayn <input_file>");
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Unable to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}


	printf("Answer to Part One: %d\n", answer1);
	printf("Answer to Part Two: %d\n", answer2);
	printf("\nTotal runtime: %f ms\n", 1000 * (double) (clock() - start) / CLOCKS_PER_SEC);
}
