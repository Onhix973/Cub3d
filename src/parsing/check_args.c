#include "parsing.h"

void	check_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len] != '\0')
		len++;
	if (len < 4)
	{
		ft_error(FILE_SHORT_ERR);
	}
	if (filename[len - 1] != 'b' || filename[len - 2] != 'u'
		|| filename[len - 3] != 'c' || filename[len - 4] != '.')
	{
		ft_error(CUB_EXT_ERR);
	}
}

void	check_arguments(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_error(N_ENOUGH_ARGS_ERR);
	}
	if (argc > 2)
	{
		ft_error(TOO_MANY_ARGS_ERR);
	}
	if (argv[1][0] == '\0')
	{
		ft_error(EMPTY_ARG_ERR);
	}
	check_extension(argv[1]);
}
