#include <stdio.h>
#include "cub3D.h"
#include "parsing.h"


int	main(int argc, char **argv)
{

	(void)argc;
	(void)argv;
	if (parsing(argc, argv) == 0)
	{
		printf("Parsing failed\n");
		return (1);
	}
	printf("SUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU");
	return (0);
}