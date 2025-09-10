#include <unistd.h>
#include "libft.h"

int	write_error(const char *message)
{
	write(2, message, ft_strlen(message));
	return (0);
}