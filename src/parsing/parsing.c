// #include "parsing.h"
// #include "gnl_noleak.h"
// #include "libft.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// /*
// 	Copy the map from the file descriptor to a string
// 	Split it in 2d array
// 	Trim whitespace for the 5 first lines
// 	Check the first word of each line for map parameters and register them as seen in the t_config tab
// 	Then check if the word is the same as the word key
// 	Put the texture path in the struct, it will be check later
// 	Check in the tab if every cardinal point has been seen
	
// 	header check is done

// 	skip all empty lines
// 	check if the map has empty lines
// 	check valid char in the map
// */

// t_config	init_config(void)
// {
// 	t_config	config;
// 	int	i;

// 	i = 0;
// 	while (i < NB_OF_MAP_PARAMS)
// 	{
// 		config.has_map_params[i] = 0;
// 		config.path[i] = NULL;
// 		i++;
// 	}
// 	config.coord[0] = 0.0f;
// 	config.coord[1] = 0.0f;
// 	config.player = 0;
// 	return (config);
// }

// char	*ft_strjoin_re(char *s1, char const *s2)
// {
// 	char	*old;
// 	size_t	i;
// 	size_t	j;

// 	i = -1;
// 	j = -1;
// 	old = s1;
// 	s1 = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!s1)
// 	{
// 		free(old);
// 		return (NULL);
// 	}
// 	while (++i < ft_strlen(old))
// 		s1[i] = old[i];
// 	while (++j < ft_strlen(s2))
// 	{
// 		s1[i] = s2[j];
// 		i++;
// 	}
// 	free(old);
// 	s1[i] = '\0';
// 	return (s1);
// }

// char *copy_map(int fd, char *map)
// {
// 	char *line;

// 	line = gnl_noleak(fd);
// 	while (line != NULL)
// 	{
// 		map = ft_strjoin_re(map, line);
// 		free(line);
// 		if (map == NULL)
// 		{
// 			ft_perror("Memory allocation failed");
// 			return (NULL);
// 		}
// 		line = gnl_noleak(fd);
// 	}
// 	printf("%s", map);
// 	return (map);
// }

// void	trim_map_params(char **map_split)
// {
// 	int	i;
// 	int	y;
// 	char *tmp;

// 	i = 0;
// 	y = NB_OF_MAP_PARAMS;
// 	while (i < y)
// 	{
// 		tmp = ft_strtrim(map_split[i], " \t");
// 		if (map_split[i][0] == '\0')
// 			y++;
// 		// check malloc
// 		free(map_split[i]);
// 		map_split[i] = tmp;
// 		i++;
// 	}
// }
// /*
// 	Compare the key and the begining of the line + if there is a space at the end of the first word
// 	Used to check cardinals points, floor and ceiling
// */
// int	check_first_word(char *line, char *key)
// {
// 	int i;

// 	i = 0;
// 	while (key[i] != '\0')
// 	{
// 		if (line[i] != key[i])
// 		{
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if (!ft_isspace(line[i]) && i > 0)
// 	{
// 		printf("something wrong with line \"%s\"\n", line);
// 		return (0);
// 	}
// 	return (1);
// }

// void	fill_path_texture(char *line, t_config *config, int k)
// {
// 	int i = 0;
// 	int y = 0;

// 	if (config->has_map_params[k] == 1)
// 		write_error("Two times the same parameter\n");
// 	config->has_map_params[k] = 1;
// 	while (ft_isalpha(line[i]))
// 	{
// 		i++;
// 	}
// 	while (ft_isspace(line[i]))
// 	{
// 		i++;
// 	}
// 	int len = ft_strlen(&line[i]);
// 	// printf("len %i\n", len);
// 	config->path[k] = malloc(sizeof(char) * (len + 1));
// 	if (config->path[k] == NULL)
// 		return ;
// 	while (line[i])
// 	{
// 		config->path[k][y] = line[i];
// 		y++;
// 		i++;
// 	}
// 	config->path[k][y] = '\0';
	
// }

// void	check_map_params(char *line, t_config *config)
// {
// 	if (check_first_word(line, "NO"))
// 		fill_path_texture(line, config, NO);
// 	else if (check_first_word(line, "SO"))
// 		fill_path_texture(line, config, SO);
// 	else if (check_first_word(line, "WE"))
// 		fill_path_texture(line, config, WE);
// 	else if (check_first_word(line, "EA"))
// 		fill_path_texture(line, config, EA);
// 	else if (check_first_word(line, "F"))
// 		fill_path_texture(line, config, FLOOR);
// 	else if (check_first_word(line, "C"))
// 		fill_path_texture(line, config, CEIL);
// 	else if (check_first_word(line, "\0"))
// 		return ;
// 	else
// 		write_error("invalid input header\n");
// }

// void check_map_whitespace(char **map, int y)
// {
// 	int i;
// 	while (map[y] != NULL)
// 	{
// 		i = 0;
// 		while (ft_isspace(map[y][i]))
// 		{
// 			i++;
// 		}
// 		printf("%s\n", map[y]);
// 		if (map[y][i] == '\0')
// 			printf("empty lines found\n");
// 		y++;
// 	}
// }

// int is_in_charset(char c, char *charset)
// {
// 	int i = 0;

// 	while (charset[i])
// 	{
// 		if (charset[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void player_config(char **map, int pos, int i, t_config *config)
// {
// 	printf("player char %c\n", config->player);
// 	if (config->player != 0)
// 	{
// 		printf("Only one player allowed\n");
// 		return ;
// 	}
// 	else
// 		config->player = map[pos][i];
// 	config->coord[0] = pos + 0.5;
// 	config->coord[1] = i + 0.5;
// 	printf("player coord %f %f", config->coord[0], config->coord[1]);
// }

// int	check_map_characters(char **map, int pos)
// {
// 	int i = 0;

// 	while(map[pos])
// 	{
// 		i = 0;
// 		while (map[pos][i])
// 		{
// 			if (!is_in_charset(map[pos][i], " 01NSEW\n"))
// 			{

// 				printf("%i %i\n", i, map[pos][i]);
// 				printf("Invalid character in map\n");
// 				return(0);
// 			}
// 			i++;
// 		}
// 		pos++;
// 	}
// 	return (1);
// }

// int get_max_len(char **map_split, int pos)
// {
// 	int len_max;
// 	int i;

// 	i = 0;
// 	len_max = 0;
// 	while (map_split[pos])
// 	{
// 		i = 0;
// 		while (map_split[pos][i])
// 		{
// 			i++;
// 		}
// 		if (i > len_max)
// 		{
// 			len_max = i;
// 		}
// 		pos++;
// 	}
// 	return (len_max);
// }

// int fill_map(char **map_split, int pos, t_config *config)
// {
// 	int i;
// 	int y;
// 	int len_max;

// 	i = 0;
// 	len_max = get_max_len(map_split, pos);
// 	while (map_split[pos])
// 	{
// 		config->map[i] = malloc(sizeof(char) * (len_max + 1));
// 		ft_memset(config->map[i], '9', len_max);
// 		if (config->map[i] == NULL)
// 			return (0);
// 		y = 0;
// 		while(map_split[pos][y])
// 		{
// 			if (is_in_charset(map_split[pos][y], " "))
// 			{
// 				y++;
// 				continue ;
// 			}
// 			if (is_in_charset(map_split[pos][y], "NSEW"))
// 			{
// 				config->coord[0] = pos + 0.5;
// 				config->coord[1] = y + 0.5;
// 			}
// 			config->map[i][y] = map_split[pos][y];
// 			y++;
// 		}
// 		config->map[i][len_max] = '\0';
// 		i++;
// 		pos++;
// 	}
// 	return (1);
// }
// int copy_new_map(char **map_split, int pos, t_config *config)
// {
// 	int	map_len;
// 	int tmp;

// 	tmp = pos;
// 	map_len = 0;
// 	while(map_split[tmp])
// 	{
// 		tmp++;
// 		map_len++;
// 	}
// 	config->map = malloc(sizeof(char *) * (map_len + 1));
// 	if (config->map == NULL)
// 		return (0);
// 	fill_map(map_split, pos, config);
// 	config->map[map_len] = NULL;
// 	return(1);
// }

// char **check_map(char *map, char **map_split, t_config *config)
// {
// 	map_split = split_with_sep(map, '\n');
	
// 	int i = 0;
// 	int y = NB_OF_MAP_PARAMS;
// 	printf("\n\nMap split lines:\n");

// 	trim_map_params(map_split);
// 	while (i < y)
// 	{
// 		printf("%s\n", map_split[i]);
// 		check_map_params(map_split[i], config);
// 		if (map_split[i][0] == '\0')
// 			y++;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < NB_OF_MAP_PARAMS)
// 	{
// 		if (config->has_map_params[i] != 1)
// 			write_error("Make sure to use NO, SO, WE, EA, F and C in the map param\n");
// 		// free everything
// 		printf("path -> %s\n", config->path[i]);
// 		i++;
// 	}
// 	printf("----------------------------\n");
// 	// skip empty lines
// 	while (map_split[y] != NULL && map_split[y][0] == '\0')
// 	{
// 		printf("%s\n", map_split[y]);
// 		y++;
// 	}
// 	printf("\n y value %i\n", y);
// 	check_map_whitespace(map_split, y);
// 	check_map_characters(map_split, y);
// 	copy_new_map(map_split, y, config);
// 	printf("\n\n\nnew map\n\n\n");
// 	i = 0;
// 	while (config->map[i])
// 	{
// 		printf("%s\n", config->map[i]);
// 		i++;
// 	}
// 	free(map);
// 	// Additional checks for the map can be added here
// 	return (map_split);
// }

// int parsing(int argc, char **argv)
// {
// 	int fd;
// 	char *map;
// 	char **map_split;
// 	t_config	config;

// 	check_arguments(argc, argv);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0) 
// 	{
// 		ft_perror(OPEN_FILE_ERR);
// 		exit(EXIT_FAILURE);
// 	}
// 	map = NULL;
// 	map = copy_map(fd, map);
// 	close(fd);
// 	if (map == NULL)
// 		return (0);
// 	map_split = NULL;
// 	config = init_config();
// 	map_split = check_map(map, map_split, &config);
// 	int i = 0;
// 	while (map_split[i] != NULL)
// 	{
// 		free(map_split[i]);
// 		i++;
// 	}
// 	free(map_split);
// 	return (1);
// }
