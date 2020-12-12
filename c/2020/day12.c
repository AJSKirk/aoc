#include <stdio.h>
#include <stdlib.h>

enum instructions {NORTH = 'N', EAST = 'E', SOUTH = 'S', WEST = 'W', 
	FORWARD = 'F', RIGHT = 'R', LEFT = 'L'};

int main(int argc, char *argv[]) {
	char cur_dir = EAST, instruction;
	int magnitude, x = 0, y = 0;
	char compass[4] = {NORTH, EAST, SOUTH, WEST};
	int cur_dir_i = 1;

	int wx = 10, wy = 1, steps, i, tmp;

	if (0) { // Insert command line switch later
		while (scanf("%c%d\n", &instruction, &magnitude) > 0) {
			if (instruction == RIGHT) {
				cur_dir_i += magnitude / 90;
				cur_dir_i %= 4;
				cur_dir = compass[cur_dir_i];
			} else if (instruction == LEFT) {
				cur_dir_i -= magnitude / 90;
				cur_dir_i = (4 + cur_dir_i) % 4;  // Handle negatives
				cur_dir = compass[cur_dir_i];
			} else { 
				if (instruction == FORWARD) {
					instruction = cur_dir;
				}
				switch (instruction) {
					case NORTH:
						y += magnitude;
						break;
					case EAST:
						x += magnitude;
						break;
					case SOUTH:
						y -= magnitude;
						break;
					case WEST:
						x -= magnitude;
						break;
					default:
						printf("Invalid instruction %c\n", instruction);
						exit(EXIT_FAILURE);
				}
			}
		}
	} else {
		while (scanf("%c%d\n", &instruction, &magnitude) > 0) switch (instruction) {
			case NORTH:
				wy += magnitude;
				break;
			case EAST:
				wx += magnitude;
				break;
			case SOUTH:
				wy -= magnitude;
				break;
			case WEST:
				wx -= magnitude;
				break;
			case FORWARD:
				x += magnitude * wx;
				y += magnitude * wy;
				break;
			case RIGHT:
				steps = magnitude / 90;
				for (i=0; i<steps; i++) {
					tmp = wx;
					wx = wy;
					wy = -tmp;
				}
				break;
			case LEFT:
				steps = magnitude / 90;
				for (i=0; i<steps; i++) {
					tmp = wx;
					wx = -wy;
					wy = tmp;
				}
				break;
			default:
				printf("Invalid instruction %c\n", instruction);
				exit(EXIT_FAILURE);
		}
	}

	printf("%d\n", abs(x) + abs(y));
	return 0;
}
