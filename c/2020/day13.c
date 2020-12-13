#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LINE_BUFFER 256
#define MAX_BUS 32


struct bus {
	long route;
	long offset;
	int slot;
};


struct bus mutual_period(struct bus *left, struct bus *right);
struct bus reduce_period(struct bus *routes, int len, struct bus acc);

int main(int argc, char *argv[]) {
	char line[LINE_BUFFER];
	char *bus_name;
	int arrive_time, bus_num, wait, min_route, min_wait = INT_MAX;
	int len = 0, slot = 0;
	struct bus routes[MAX_BUS], start_acc = {1, 1};

	fgets(line, LINE_BUFFER, stdin);
	arrive_time = atoi(line);

	fgets(line, LINE_BUFFER, stdin);
	for (bus_name=strtok(line, ",\n"); bus_name; bus_name=strtok(NULL, ",\n")) {
		if (*bus_name != 'x') {
			routes[len].route = atoi(bus_name);
			routes[len].offset = (routes[len].route - (slot % routes[len].route)) % routes[len].route;
			wait = routes[len].route - (arrive_time % routes[len].route);
			if (wait < min_wait) {
				min_wait = wait;
				min_route = routes[len].route;
			}
			len++;
		}
		slot++;
	}


	printf("Min Wait * First Route: %d\n", min_wait * min_route);
	printf("Earliest Offset: %ld\n", reduce_period(routes, len, start_acc).offset);

	return 0;
}

struct bus mutual_period(struct bus *left, struct bus *right) {
	long i;
	struct bus out;
	for (i=left->offset; i<=left->route*right->route; i+=left->route) {
		if (i != 0 && i % right->route == right->offset) {
			out.route = left->route * right->route;
			out.offset = i;
			return out;
		}
	}
	printf("Unable to find mutual period between %ld and %ld\n", left->route, right->route);
	exit(EXIT_FAILURE);
}

struct bus reduce_period(struct bus *routes, int len, struct bus acc) {
	if (len == 0)
		return acc;

	acc = mutual_period(&acc, routes);
	return reduce_period(&routes[1], len - 1, acc);
}
