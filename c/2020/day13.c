#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LINE_BUFFER 256


int main(int argc, char *argv[]) {
	char line[LINE_BUFFER];
	int len = LINE_BUFFER;
	char *bus_name;
	int arrive_time, bus_num, wait, min_route, min_wait = INT_MAX;

	fgets(line, LINE_BUFFER, stdin);
	arrive_time = atoi(line);

	fgets(line, LINE_BUFFER, stdin);
	for (bus_name=strtok(line, ",\n"); bus_name; bus_name=strtok(NULL, ",\n")) {
		if (*bus_name == 'x') {
			continue;
		}
		bus_num = atoi(bus_name);
		wait = bus_num - (arrive_time % bus_num);
		if (wait < min_wait) {
			min_wait = wait;
			min_route = bus_num;
		}
	}

	printf("%d\n", min_wait * min_route);

	return 0;
}
