#include "parsing.h"
#include "gnl_noleak.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin_re(char *s1, char const *s2)
{
	char	*old;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	old = s1;
	s1 = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1)
	{
		free(old);
		return (NULL);
	}
	while (++i < ft_strlen(old))
		s1[i] = old[i];
	while (++j < ft_strlen(s2))
	{
		s1[i] = s2[j];
		i++;
	}
	free(old);
	s1[i] = '\0';
	return (s1);
}

char *copy_map(int fd, char *map)
{
	char *line;

	line = gnl_noleak(fd);
	while (line != NULL)
	{
		map = ft_strjoin_re(map, line);
		free(line);
		if (map == NULL)
		{
			ft_perror("Memory allocation failed");
			return (NULL);
		}
		line = gnl_noleak(fd);
	}
	printf("%s", map);
	return (map);
}

char **check_map(char *map, char **map_split)
{

	map_split = ft_split(map, '\n');
	
	int i = 0;
	while (map_split[i] != NULL)
	{
		printf("%s\n", map_split[i]);
		i++;
	}
	free(map);
	// Additional checks for the map can be added here
	return (map_split);
}

int parsing(int argc, char **argv)
{
	int fd;
	char *map;
	char **map_split;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) 
	{
		ft_perror(OPEN_FILE_ERR);
		exit(EXIT_FAILURE);
	}
	map = NULL;
	map = copy_map(fd, map);
	close(fd);
	if (map == NULL)
		return (0);
	map_split = NULL;
	map_split = check_map(map, map_split);
	int i = 0;
	while (map_split[i] != NULL)
	{
		free(map_split[i]);
		i++;
	}
	free(map_split);
	return (1);
}

// 6 elements to check: NO, SO, WE, EA, F, C