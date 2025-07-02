#ifndef PARSING_H
# define PARSING_H

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLD	"\033[1m"
#define RESET   "\033[0m"

/*CHECK ARGS*/
void check_extension(char *filename);
void check_arguments(int argc, char **argv);

int	parsing(int argc, char **argv);

/*UTILS*/
void	ft_error(const char *message);
void	ft_perror(const char *message);
#endif