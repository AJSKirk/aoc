#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_BUFFER 128
#define MAX_FIELDS 24
#define MAX_RANGES 2  // Dynamic allocation? Never heard of it
#define NAME_BUFFER 24
#define MAX_TICKETS 256

struct range {
	int min;
	int max;
};

struct field {
	char name[NAME_BUFFER];
	int nranges;
	struct range ranges[MAX_RANGES];
};

typedef unsigned int set_t;  // 32 bits big enough here

unsigned int check_valid(struct field rule, int value);

int main(int argc, char *argv[]) {
	char line[LINE_BUFFER], *range_str, *value_str, *next_row;
	struct field fields[MAX_FIELDS];

	int i = 0, j, num_fields;
	int error_rate = 0, value;
	set_t valid_fields[MAX_TICKETS];

	// Parse rules
	for (fgets(line, LINE_BUFFER, stdin); line[0] != '\n'; fgets(line, LINE_BUFFER, stdin)) {
		strncpy(fields[i].name, strtok(line, ":"), NAME_BUFFER);
		fields[i].nranges = 0;
		for (range_str=strtok(NULL, " or\n"); range_str!=NULL; range_str=strtok(NULL, "or\n")) {
			sscanf(range_str, "%d-%d", &fields[i].ranges[fields[i].nranges].min, &fields[i].ranges[fields[i].nranges].max);
			fields[i].nranges++;
		}
		i++;
	}
	num_fields = i;

	// Skip my ticket
	for (fgets(line, LINE_BUFFER, stdin); line[0] != 'n'; fgets(line, LINE_BUFFER, stdin)) {;};

	// Parse nearby tickets
	i = 0;
	for (next_row=fgets(line, LINE_BUFFER, stdin); next_row!=NULL; next_row=fgets(line, LINE_BUFFER, stdin)) {
		for (value_str=strtok(line, ",\n"); value_str!=NULL; value_str=strtok(NULL, ",\n")) {
			value = atoi(value_str);
			valid_fields[i] = 0U;
			for (j=0; j<num_fields; j++) {
				valid_fields[i] |= check_valid(fields[j], value) << j;
			}
			if (valid_fields[i] == 0)
				error_rate += value;
		}
		i++;
		if (i >= MAX_TICKETS) {
			printf("Ticket buffer overrun\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("%d\n", error_rate);

	return 0;
}

unsigned int check_valid(struct field rule, int value) {
	int i;
	for (i=0; i<rule.nranges; i++) {
		if (value >= rule.ranges[i].min && value <= rule.ranges[i].max)
			return 1U;
	}
	return 0U;
}
