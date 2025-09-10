#ifndef MAPGEN_H
# define MAPGEN_H

# define MALLOC_ERR "Error:\nMemory allocation failed\n"

typedef enum e_card
{
	N, S, W, E
} 	t_card;

typedef struct s_mapgen
{
	char **map;
	int width;
	int height;
	int player_x;
	int player_y;
	int area;
} t_mapgen;

/* UTILS */
void border_walls(t_mapgen *cfg, char c);
void free_split(char **split);

void rand_position_player(t_mapgen *cfg);
int random_direction(void);

void init_config(t_mapgen *config);
void print_map(char **map);
int	write_error(const char *message);

#endif