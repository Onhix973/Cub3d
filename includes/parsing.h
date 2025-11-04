#ifndef PARSING_H
# define PARSING_H

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BOLD	"\033[1m"
# define RESET   "\033[0m"
# define FILE_SHORT_ERR 		"Filename too short"
# define CUB_EXT_ERR 			"Expected .cub file"
# define N_ENOUGH_ARGS_ERR 		"Not enough arguments"
# define TOO_MANY_ARGS_ERR 		"Too many arguments provided"
# define EMPTY_ARG_ERR 			"Empty argument"
# define OPEN_FILE_ERR			"Can't open map"
# define RGB_FMT_ERR			"Error:\nRGB format must be R,G,B\n"
# define MALLOC_ERR		"Error:\nMemory allocation failed\n"
# define ONE_PLAYER_ERR	"Error:\nthere must be exactly one player in the map\n"

# include "structs.h"
# include <stdbool.h>

typedef struct s_config		t_config;
typedef struct s_map		t_map;
typedef struct s_context	t_context;

/*CHECK ARGS*/
void	check_extension(char *filename);
void	check_arguments(int argc, char **argv);

/* CONTEXT CREATOR */
void	context_creator(int argc, char **argv, t_context *ctx);

/* LOAD LINES */
int		load_lines(int fd, char ***out_lines);

/* HEADER PARSING */
int		parse_header(char **lines, t_config *conf);
int		parsing(int argc, char **argv);
int		fill_texture(t_config *conf, const char *line);

int		check_close(const t_map *map);

/* MAP SYNTAX */
int		valid_map_syntax(char **map_lines, t_context *ctx);
int		extract_map_only(char **lines, t_config *conf, char ***out_map_lines);

/* MAP BUILD */
int		rect_map(char **map_lines, t_map *map);

/*UTILS*/
void	config_init(t_config *c);
void	map_init(t_map *m);
void	ctx_init(t_context *ctx);

int		count_fields(const char *s, char c);
void	free_split(char **split);
int		free_and_return_int(char *val, int ret);

void	ft_error(const char *message);
void	ft_perror(const char *message);
int		write_error(const char *message);

char	**split_with_sep(char const *line, char sep);
char	*ft_strjoin_re(char *s1, char const *s2);
void	map_free(t_map *m);
void	rgb_to_hex(int rgb[3], int *hex);

/*UTILS IS SPACE*/
int		ft_isspaces(char c);
int		is_space_or_tab(char c);
int		is_blank_line(char *s);
int		skip_spaces(const char *s, int i);

/* UTILS PARSE_HEADER */
int		check_first_word(const char *line, char *key);
char	*dup_last_word(const char *s);

/*UTILS PARSE RGB*/
int		parse_color_line(int dst[3], char *value);

void	config_free(t_config *c);
void context_free(t_context *ctx, bool free_map);

#endif