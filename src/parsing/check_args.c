#include <unistd.h>
#include "parsing.h"
#include "cub3D.h"


void check_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len] != '\0')
		len++;
	if (len < 4)
	{
		ft_error("Error: Filename too short");
	}
	if (filename[len - 1] != 'b' || filename[len - 2] != 'u'
		|| filename[len - 3] != 'c' || filename[len - 4] != '.')
	{
		ft_error("Error: Expected .cub file");
	}

}

void check_arguments(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_error("Not enough arguments");
	}
	if (argc > 2)
	{
		ft_error("Error: Too many arguments provided");
	}
	if (argv[1][0] == '\0')
	{
		ft_error("Error: Empty argument");
	}
	check_extension(argv[1]);
}