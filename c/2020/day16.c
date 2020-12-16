#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_BUFFER 128
#define MAX_FIELDS 24
#define MAX_RANGES 2  // Dynamic allocation? Never heard of it
#define NAME_BUFFER 24

struct range {
	int min;
	int max;
};

struct field {
	char name[NAME_BUFFER];
	int nranges;
	struct range ranges[MAX_RANGES];
	int position;
};

typedef unsigned int set_t;  // 32 bits big enough here

unsigned int check_valid(struct field rule, int value);
void zero_bit(set_t *fields, int bit, int len);
unsigned int find_set_bit(set_t set);

int main(int argc, char *argv[]) {
	char line[LINE_BUFFER], *range_str, *value_str, *next_row;
	struct field fields[MAX_FIELDS];

	int i = 0, j, num_fields, num_tickets, num_locked;
	int error_rate = 0, value, bit;
	set_t global_valid[MAX_FIELDS];
	set_t local_valid;
	set_t locked;
	int *my_ticket;
	long product;

	// Parse rules
	for (fgets(line, LINE_BUFFER, stdin); line[0] != '\n'; fgets(line, LINE_BUFFER, stdin)) {
		strncpy(fields[i].name, strtok(line, ":"), NAME_BUFFER);
		fields[i].nranges = 0;
		for (range_str=strtok(NULL, " or\n"); range_str!=NULL; range_str=strtok(NULL, "or\n")) {
			sscanf(range_str, "%d-%d", &fields[i].ranges[fields[i].nranges].min, &fields[i].ranges[fields[i].nranges].max);
			fields[i].nranges++;
		}
		global_valid[i] = ~0;
		i++;
	}
	num_fields = i;

	my_ticket = (int *) malloc(num_fields * sizeof(int));
	i = 0;
	// Save my ticket
	for (fgets(line, LINE_BUFFER, stdin); line[0] != 'n'; fgets(line, LINE_BUFFER, stdin)) {
		if (isdigit(line[0])) {
			for (value_str=strtok(line, ",\n"); value_str!=NULL; value_str=strtok(NULL, ",\n")) {
				my_ticket[i] = atoi(value_str);
				i++;
			}
		}
	}

	// Parse nearby tickets
	for (next_row=fgets(line, LINE_BUFFER, stdin); next_row!=NULL; next_row=fgets(line, LINE_BUFFER, stdin)) {
		i = 0;
		for (value_str=strtok(line, ",\n"); value_str!=NULL; value_str=strtok(NULL, ",\n")) {
			value = atoi(value_str);
			local_valid = 0U;
			for (j=0; j<num_fields; j++) {
				local_valid |= check_valid(fields[j], value) << j;
			}
			if (local_valid == 0)
				error_rate += value;
			else
				global_valid[i] &= local_valid;
			i++;
		}
	}

	// Identify fields
	num_locked = 0;
	locked = 0U;
	while (num_locked < num_fields) {
		for (i=0; i<num_fields; i++) {
			if (((locked >> i) & 1U) == 0 && (global_valid[i] & (global_valid[i] - 1)) == 0) {  // Neat trick from K&R to zero rightmost nonzero bit
				bit = find_set_bit(global_valid[i]);
				fields[bit].position = i;
				zero_bit(global_valid, bit, num_fields);
				num_locked++;
				locked |= 1U << i;
			}
		}
	}

	// Compute product
	product = 1;
	for (i=0; i<num_fields; i++) {
		if (strncmp(fields[i].name, "departure", 9) == 0) {
			product *= my_ticket[fields[i].position];
		}
	}

	printf("Scanning Error Rate: %d\n", error_rate);
	printf("Departure Product: %ld\n", product);

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

void zero_bit(set_t *fields, int bit, int len) {
	int i;
	for (i=0; i<len; i++) {
		if (fields[i] == 1U << bit)
			continue;
		fields[i] &= ~(1U << bit);
	}
}

unsigned int find_set_bit(set_t set) {
	// Assumes only one bit set
	int i;
	for (i=0; i<8*sizeof(set_t); i++) {
		if (set >> i == 1U)
			return i;
	}
	return 0;
}
