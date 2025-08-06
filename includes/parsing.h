#ifndef PARSING_H
# define PARSING_H

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLD	"\033[1m"
#define RESET   "\033[0m"

#define FILE_SHORT_ERR 		"Filename too short"
#define CUB_EXT_ERR 		"Expected .cub file"
#define N_ENOUGH_ARGS_ERR 	"Not enough arguments"
#define TOO_MANY_ARGS_ERR 	"Too many arguments provided"
#define EMPTY_ARG_ERR 		"Empty argument"
#define OPEN_FILE_ERR		"Can't open map"

/*CHECK ARGS*/
void check_extension(char *filename);
void check_arguments(int argc, char **argv);

int	parsing(int argc, char **argv);

/*UTILS*/
void	ft_error(const char *message);
void	ft_perror(const char *message);
#endif