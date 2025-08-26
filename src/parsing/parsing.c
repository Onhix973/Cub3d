#include "parsing.h"
#include "gnl_noleak.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
	Copy the map from the file descriptor to a string
	Split it in 2d array
	Trim whitespace for the 5 first lines
	Check the first word of each line for map parameters and register them as seen in the t_config tab
	Then check if the word is the same as the word key
	Put the texture path in the struct, it will be check later
	Check in the tab if every cardinal point has been seen
	
	header check is done

	skip all empty lines
	check if the map has empty lines

*/

t_config	init_config(void)
{
	t_config	config;
	int	i;

	i = 0;
	while (i < NB_OF_MAP_PARAMS)
	{
		config.has_map_params[i] = 0;
		config.path[i] = NULL;
		i++;
	}
	return (config);
}

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

void	trim_map_params(char **map_split)
{
	int	i;
	int	y;
	char *tmp;

	i = 0;
	y = NB_OF_MAP_PARAMS;
	while (i < y)
	{
		tmp = ft_strtrim(map_split[i], " \t");
		if (map_split[i][0] == '\0')
			y++;
		// check malloc
		free(map_split[i]);
		map_split[i] = tmp;
		i++;
	}
}
/*
	Compare the key and the begining of the line + if there is a space at the end of the first word
	Used to check cardinals points, floor and ceiling
*/
int	check_first_word(char *line, char *key)
{
	int i;

	i = 0;
	while (key[i] != '\0')
	{
		if (line[i] != key[i])
		{
			return (0);
		}
		i++;
	}
	if (!ft_isspace(line[i]) && i > 0)
	{
		printf("something wrong with line \"%s\"\n", line);
		return (0);
	}
	return (1);
}

void	fill_path_texture(char *line, t_config *config, int k)
{
	int i = 0;
	int y = 0;

	if (config->has_map_params[k] == 1)
		write_error("Two times the same parameter\n");
	config->has_map_params[k] = 1;
	while (ft_isalpha(line[i]))
	{
		i++;
	}
	while (ft_isspace(line[i]))
	{
		i++;
	}
	int len = ft_strlen(&line[i]);
	// printf("len %i\n", len);
	config->path[k] = malloc(sizeof(char) * (len + 1));
	if (config->path[k] == NULL)
		return ;
	while (line[i])
	{
		config->path[k][y] = line[i];
		y++;
		i++;
	}
	config->path[k][y] = '\0';
	
}

void	check_map_params(char *line, t_config *config)
{
	if (check_first_word(line, "NO"))
		fill_path_texture(line, config, NO);
	else if (check_first_word(line, "SO"))
		fill_path_texture(line, config, SO);
	else if (check_first_word(line, "WE"))
		fill_path_texture(line, config, WE);
	else if (check_first_word(line, "EA"))
		fill_path_texture(line, config, EA);
	else if (check_first_word(line, "F"))
		fill_path_texture(line, config, FLOOR);
	else if (check_first_word(line, "C"))
		fill_path_texture(line, config, CEIL);
	else if (check_first_word(line, "\0"))
		return ;
	else
		write_error("invalid input header\n");
}

void check_map_whitespace(char **map, int y)
{
	int i;
	while (map[y] != NULL)
	{
		i = 0;
		while (ft_isspace(map[y][i]))
		{
			i++;
		}
		printf("%s\n", map[y]);
		if (map[y][i] == '\0')
			printf("empty lines found\n");
		y++;
	}
}

char **check_map(char *map, char **map_split, t_config *config)
{

	map_split = split_with_sep(map, '\n');
	
	int i = 0;
	int y = NB_OF_MAP_PARAMS;
	printf("\n\nMap split lines:\n");

	trim_map_params(map_split);
	while (i < y)
	{
		printf("%s\n", map_split[i]);
		check_map_params(map_split[i], config);
		if (map_split[i][0] == '\0')
			y++;
		i++;
	}
	i = 0;
	while (i < NB_OF_MAP_PARAMS)
	{
		if (config->has_map_params[i] != 1)
			write_error("Make sure to use NO, SO, WE, EA, F and C in the map param\n");
		// free everything
		printf("path -> %s\n", config->path[i]);
		i++;
	}
	printf("----------------------------\n");
	// skip empty lines
	while (map_split[y] != NULL && map_split[y][0] == '\0')
	{
		printf("%s\n", map_split[y]);
		y++;
	}
	check_map_whitespace(map_split, y);
	free(map);
	// Additional checks for the map can be added here
	return (map_split);
}

int parsing(int argc, char **argv)
{
	int fd;
	char *map;
	char **map_split;
	t_config	config;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) 
	{
		ft_perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	map = NULL;
	map = copy_map(fd, map);
	close(fd);
	if (map == NULL)
		return (0);
	map_split = NULL;
	config = init_config();
	map_split = check_map(map, map_split, &config);
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