#ifndef PARSING_H
# define PARSING_H

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLD	"\033[1m"
#define RESET   "\033[0m"
#define NB_OF_MAP_PARAMS 6

typedef enum r_cardinals
{
	NO, SO, WE, EA, FLOOR, CEIL
} t_cardinals;

typedef struct s_config
{
	int seen[NB_OF_MAP_PARAMS];
	char *path[4];
	int floor[3];
	int ceil[3];
	int	i_map_start;
}	t_config;

typedef struct s_map
{
	char **grid;
	int width;
	int height;
	int player_x;
	int player_y;
	char player_dir;
} t_map;

typedef struct s_context
{
	t_config conf;
	t_map	map;
	char	**lines;
} t_context;

#define FILE_SHORT_ERR 		"Filename too short"
#define CUB_EXT_ERR 		"Expected .cub file"
#define N_ENOUGH_ARGS_ERR 	"Not enough arguments"
#define TOO_MANY_ARGS_ERR 	"Too many arguments provided"
#define EMPTY_ARG_ERR 		"Empty argument"
#define OPEN_FILE_ERR		"Can't open map"

/*CHECK ARGS*/
void check_extension(char *filename);
void check_arguments(int argc, char **argv);
int	load_lines(int fd, char ***out_lines);
int parse_header(char **lines, t_config *conf);

int	parsing(int argc, char **argv);

/* MAP SYNTAX */
int valid_map_syntax(char **map_lines, t_context *ctx);
int	extract_map_only(char **lines, t_config *conf, char ***out_map_lines);

/* MAP BUILD */
int rect_map(char **map_lines, t_map *map);


/*UTILS*/
void	ft_error(const char *message);
void	ft_perror(const char *message);
int		write_error(const char *message);
char 	**split_with_sep(char const *line, char sep);
void 	map_free(t_map *m);
void	free_split(char **split);

/*UTILS IS SPACE*/
int		ft_isspaces(char c);
int		is_space_or_tab(char c);
int 	is_blank_line(char *s);
int 	skip_spaces(const char *s, int i);

/*UTILS PARSE RGB*/
int		parse_color_line(int dst[3], char *value);


void	config_init(t_config *c);
void	map_init(t_map *m);
void	ctx_init(t_context *ctx);


#endif