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
	int has_map_params[NB_OF_MAP_PARAMS];
	char *path[NB_OF_MAP_PARAMS];
}	t_config;


/*CHECK ARGS*/
void check_extension(char *filename);
void check_arguments(int argc, char **argv);

int	parsing(int argc, char **argv);

/*UTILS*/
void	ft_error(const char *message);
void	ft_perror(const char *message);
void	write_error(const char *message);
char **split_with_sep(char const *line, char sep);
int	ft_isspace(char c);

#endif