#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TILE_SIZE 10
#define MAX_TILES 150
#define GLOBAL_DIM 20

struct tile {
	int id;
	char grid[TILE_SIZE][TILE_SIZE];
	int borders[8];  // Treating chars as binary flags admits an integer representation!
	int arrange[8][4];  // Len 4 vec of border values for each possible arrangement
	int placed;
};

struct assignment {
	int tile_idx;
	int arrangement;
};

struct tile tiles[MAX_TILES];
int *border_counts = NULL;
struct assignment *map = NULL;
int dimension;

enum sides {TOP, TOP_F, LEFT, LEFT_F, BOTTOM, BOTTOM_F, RIGHT, RIGHT_F};
// Clockwise rotations and vertical mirroring
enum arrangements {ARR_0, ARR_90, ARR_180, ARR_270, ARR_FLIP_0, ARR_FLIP_90, ARR_FLIP_180, ARR_FLIP_270};


void cache_borders(void);
int binary_value(char *border);
int num_unmatched_borders(struct tile t, int arrangement);
char **place_tiles(int num_tiles);
int tile_fits(int i, int j, struct tile t, int arrangement);
int get_targ_unmatched(int i, int j);
int map_complete(int num_tiles);
char **join_tiles(void);
void arrange_grid(char **grid, int size, int arrangement);
char **grid_to_ptrs(char grid[][TILE_SIZE]);
int score_roughness(char **map, int size);

int main(int argc, char *argv[]) {
	char line[TILE_SIZE+2], *next;
	int i = 0, j, arrange;
	long long corner_mult = 1;
	char **map, **rot_map;
	int roughness;

	// For all possible borders, so careful with big tiles (fine here though, 2^8 == 256)
	border_counts = calloc((int) pow(2, TILE_SIZE), sizeof(int));  // Need to calloc here for dynamic sizing

	for (next=fgets(line, TILE_SIZE+2, stdin); next!=NULL; next=fgets(line, TILE_SIZE+2, stdin)) {
		if (line[0] == '\n') {
			i++;
			continue;
		} else if (line[0] == 'T') {
			strtok(line, " ");
			tiles[i].id = atoi(strtok(NULL, ":"));
			j = 0;
		} else {
			strncpy(tiles[i].grid[j++], line, TILE_SIZE);
		}
	}
	cache_borders();

	// Part 1 product
	i = 0;
	while (tiles[i].id != 0) {
		for (j=0; j<8; j++)
			if (num_unmatched_borders(tiles[i], j) == 2) {
				corner_mult *= tiles[i].id;
				break;
			}
		i++;
	}

	map = place_tiles(i);
	for (arrange=0; arrange<8; arrange++) {
		rot_map = (char **) malloc(dimension * (TILE_SIZE - 2) * sizeof(char *));
		for (i=0; i<dimension * (TILE_SIZE - 2); i++) {
			rot_map[i] = (char *) malloc(dimension * (TILE_SIZE - 2) * sizeof(char));
			strncpy(rot_map[i], map[i], dimension * (TILE_SIZE - 2));
		}


		arrange_grid(rot_map, dimension * (TILE_SIZE - 2), arrange);
		printf("%d\n", score_roughness(rot_map, dimension * (TILE_SIZE - 2)));

		for (i=0; i<dimension * (TILE_SIZE - 2); i++)
			free(rot_map[i]);
		free(rot_map);
	}

	printf("%lld\n", corner_mult);

	return 0;
}


void cache_borders(void) {
	int i = 0, j, k;
	char border_strs[8][TILE_SIZE];
	while (tiles[i].id != 0) {  // Externals are always set to zero
		j = 0;
		for (j=0; j<TILE_SIZE; j++) {
			border_strs[TOP][j] = tiles[i].grid[0][j];                              
			border_strs[TOP_F][j] = tiles[i].grid[0][TILE_SIZE - 1 - j];           
			border_strs[LEFT][j] = tiles[i].grid[j][0];                           
			border_strs[LEFT_F][j] = tiles[i].grid[TILE_SIZE - 1 - j][0];        
			border_strs[BOTTOM][j] = tiles[i].grid[TILE_SIZE - 1][j];                
			border_strs[BOTTOM_F][j] = tiles[i].grid[TILE_SIZE - 1][TILE_SIZE - 1 - j];
			border_strs[RIGHT][j] = tiles[i].grid[j][TILE_SIZE - 1];                
			border_strs[RIGHT_F][j] = tiles[i].grid[TILE_SIZE - 1 - j][TILE_SIZE - 1];
		}
		for (j=0; j<8; j++) {
			tiles[i].borders[j] = binary_value(border_strs[j]);
			border_counts[tiles[i].borders[j]]++;
		}

		// Faster than calculating from matrix products, and too tired to figure out a tricky modulo loop to do it
		tiles[i].arrange[0][0] = tiles[i].arrange[3][3] = tiles[i].arrange[5][1] = tiles[i].arrange[6][2] = tiles[i].borders[TOP];
		tiles[i].arrange[1][1] = tiles[i].arrange[2][2] = tiles[i].arrange[4][0] = tiles[i].arrange[7][3] = tiles[i].borders[TOP_F];
		tiles[i].arrange[0][1] = tiles[i].arrange[1][2] = tiles[i].arrange[4][3] = tiles[i].arrange[5][0] = tiles[i].borders[LEFT];
		tiles[i].arrange[2][3] = tiles[i].arrange[3][0] = tiles[i].arrange[6][1] = tiles[i].arrange[7][2] = tiles[i].borders[LEFT_F];
		tiles[i].arrange[0][2] = tiles[i].arrange[3][1] = tiles[i].arrange[5][3] = tiles[i].arrange[6][0] = tiles[i].borders[BOTTOM];
		tiles[i].arrange[1][3] = tiles[i].arrange[2][0] = tiles[i].arrange[4][2] = tiles[i].arrange[7][1] = tiles[i].borders[BOTTOM_F];
		tiles[i].arrange[0][3] = tiles[i].arrange[1][0] = tiles[i].arrange[4][1] = tiles[i].arrange[5][2] = tiles[i].borders[RIGHT];
		tiles[i].arrange[2][1] = tiles[i].arrange[3][2] = tiles[i].arrange[6][3] = tiles[i].arrange[7][0] = tiles[i].borders[RIGHT_F];
		
		i++;
	}
}


int binary_value(char *border) {
	int i;
	int res = 0;

	for (i=0; i<TILE_SIZE; i++) {
		res += border[i] == '#';
		res <<= 1;
	}
	res >>= 1;

	return res;
}

int num_unmatched_borders(struct tile t, int arrangement) {
	int i;
	int count = 0;
	for (i=0; i<4; i++) 
		if (border_counts[t.arrange[arrangement][i]] == 1)
			count++;

	return count;
}

char **place_tiles(int num_tiles) {
	dimension = (int) sqrt(num_tiles);  // Assumes square map (true for our input)
	int i, j, cand;
	int targ_unmatched, arrangement;
	int arr_start, start_seed = 0;

	map = (struct assignment *) malloc(num_tiles * sizeof(struct assignment));

	do {
		for (i=0; i<num_tiles; i++) {
			map[i].tile_idx = -1;
			map[i].arrangement = -1;
			tiles[i].placed = 0;
		}

		for (i=0; i<dimension; i++) {
			for (j=0; j<dimension; j++) {
				targ_unmatched = get_targ_unmatched(i, j);
				for (cand=0; cand<num_tiles; cand++) {
					if (map[i * dimension + j].tile_idx != -1)
						break;
					if (!tiles[cand].placed) {
						arr_start = (i == 0 && j == 0) ? start_seed : 0;
						for (arrangement=arr_start; arrangement<8; arrangement++) {
							if (targ_unmatched == num_unmatched_borders(tiles[cand], arrangement) &&
									tile_fits(i, j, tiles[cand], arrangement)) {
								map[i * dimension + j].tile_idx = cand;
								map[i * dimension + j].arrangement = arrangement;
								tiles[cand].placed = 1;
								break;
							}
						}
					}
				}
			}
		}
	start_seed++;
	} while(!map_complete(num_tiles));

	return join_tiles();
}

int map_complete(int num_tiles) {
	int i;
	for (i=0; i<num_tiles; i++)
		if (map[i].tile_idx == -1)
			return 0;
	return 1;
}

int get_targ_unmatched(int i, int j) {
	if ((i == j && j == 0) || (i == j && j == dimension - 1) || (i == 0 && j == dimension - 1) || (i == dimension - 1 && j == 0))
		return 2;
	else if (i == 0 || j == 0 || i == dimension - 1 || j == dimension - 1)
		return 1;
	else
		return 0;
}

int tile_fits(int i, int j, struct tile t, int arrangement) {
	// Note encoding order - Neighbour n[k] has border index k (TOP-LEFT-BOTTOM-RIGHT) facing target
	int neighbours[4][2] = {{i + 1, j}, {i, j + 1}, {i - 1, j}, {i, j - 1}};
	int k;
	struct assignment neighbour_assignment;
	int neighbour_border;
	
	for (k=0; k<4; k++) {
		// Autopass if neighbour would be off the edge
		if (neighbours[k][0] < 0 || neighbours[k][1] < 0 || neighbours[k][0] >= dimension || neighbours[k][1] >= dimension)
			continue;
		// Autopass if neighbour is uninitialised
		neighbour_assignment = map[neighbours[k][0] * dimension + neighbours[k][1]];
		if (neighbour_assignment.tile_idx == -1)
			continue;
		neighbour_border = tiles[neighbour_assignment.tile_idx].arrange[neighbour_assignment.arrangement][k];
		if (neighbour_border != t.arrange[arrangement][(k + 2) % 4])
			return 0;
	}
	return 1;  // Everything passed
}

char **join_tiles(void) {
	char **borderless_map = (char **) malloc(dimension * (TILE_SIZE - 2) * sizeof(char *));
	int row, col, tile_row, tile_col, row_of_tile;
	char **rotated_grid;
	struct assignment tile_assignment;




	for (tile_row=0; tile_row<dimension; tile_row++) {
		for (row_of_tile=1; row_of_tile<TILE_SIZE-1; row_of_tile++) {
			row = tile_row * (TILE_SIZE - 2) + row_of_tile - 1;
			borderless_map[row] = (char *) malloc(dimension * (TILE_SIZE - 2) * sizeof(char));
			for (tile_col=0; tile_col<dimension; tile_col++) {
				tile_assignment = map[tile_row * dimension + tile_col];
				rotated_grid = grid_to_ptrs(tiles[tile_assignment.tile_idx].grid);
				arrange_grid(rotated_grid, TILE_SIZE, tile_assignment.arrangement);
				strncpy(&borderless_map[row][tile_col * (TILE_SIZE - 2)], &rotated_grid[row_of_tile][1], TILE_SIZE - 2);
				free(rotated_grid);
			}
		}
	}

	return borderless_map;
}

char **grid_to_ptrs(char grid[][TILE_SIZE]) {
	char **out = (char **) malloc(TILE_SIZE * sizeof(char *));
	int i;

	for (i=0; i<TILE_SIZE; i++) {
		out[i] = malloc(TILE_SIZE * sizeof(char));
		strncpy(out[i], grid[i], TILE_SIZE);
	}
	return out;
}

void arrange_grid(char **grid, int size, int arrangement) {
	int flip = arrangement / 4;
	int rotations = arrangement % 4;
	int i, j;

	char newgrid[size][size];
	char row[size];  // Temporary storage for flip

	if (flip) {
		for (i=0; i<size; i++) {
			for (j=0; j<size; j++)
				row[j] = grid[i][size - 1 - j];
			for (j=0; j<size; j++)
				grid[i][j] = row[j];
		}
	}

	for (; rotations > 0; rotations--) {
		for (i=0; i<size; i++)
			for (j=0; j<size; j++)
				newgrid[i][j] = grid[j][size - 1 - i];

		for (i=0; i<size; i++)
			for (j=0; j<size; j++)
				grid[i][j] = newgrid[i][j];
	}
}

int check_monster(char **map, int row, int col) {
	char monster[3][20] = {"..................#.", "#....##....##....###", ".#..#..#..#..#..#..."};
	int i, j;

	for (i=0; i<3; i++)
		for (j=0; j<20; j++)
			if (monster[i][j] == '#' && map[row + i][col + j] != '#')
				return 0;

	return 1;
}

int count_monsters(char **map, int size) {
	int i, j;
	int monsters = 0;

	for (i=0; i<size - 2; i++)
		for (j=0; j<size - 19; j++)
			monsters += check_monster(map, i, j);

	return monsters;
}

int score_roughness(char **map, int size) {
	int hashes = 0;
	int i, j;

	for (i=0; i<size; i++)
		for (j=0; j<size; j++)
			hashes += (map[i][j] == '#');

	return hashes - 15 * count_monsters(map, size);
}
