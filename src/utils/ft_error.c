
#include "cub3D.h"
#include "libft.h"
#include <parsing.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	ft_error(const char *message)
{
	if (message)
	{
		write(2, RED, 5);
		write(2, "Error: \n", 8);
		write(2, RESET, 4);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}

void ft_perror(const char *message)
{
	const char *sys_mess;

	sys_mess = strerror(errno);
	write(2, RED, 6);
	write(2, BOLD, 4);
	write(2, message, strlen(message));
	write(2, RESET, 4);
	write(2, ": \n", 3);
	write(2, sys_mess, strlen(sys_mess));
	write(2, "\n", 1);
}

void	write_error(const char *message)
{
	write(2, message, ft_strlen(message));
}