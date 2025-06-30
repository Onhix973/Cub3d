
#include "cub3D.h"
#include "libft.h"

void	ft_error(const char *message)
{
	if (message)
	{
		write(2, RED, 5);
		write(2, "Error: ", 7);
		write(2, RESET, 4);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}