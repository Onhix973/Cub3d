#include <stdlib.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	free_and_return_int(char *val, int ret)
{
	free(val);
	return (ret);
}
