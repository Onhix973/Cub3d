#include "parsing.h"
#include <stdlib.h>
#include "libft.h"

int is_allowed_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

int count_lines(char **lines)
{
	int i = 0;
	while (lines[i])
		i++;
	return (i);
}


int	extract_map_only(char **lines, t_config *conf, char ***out_map_lines)
{
	int		count;
	int		i;
	int		j;
	char	**dst;

	*out_map_lines = NULL;
	i = conf->i_map_start;
	count = count_lines(&lines[conf->i_map_start]);
	dst = (char **)malloc(sizeof(char *) * (count + 1));
	if (dst == NULL)
		return (write_error("Error\nmalloc failed\n"));
	i = conf->i_map_start;
	j = 0;
	while (lines[i] != NULL)
	{
		dst[j] = ft_strdup(lines[i]);
		if (dst[j] == NULL)
		{
			free_split(dst);
			return (write_error("Error\nmalloc failed\n"));
		}
		j++;
		i++;
	}
	dst[j] = NULL;
	*out_map_lines = dst;
	return (1);
}

int valid_map_syntax(char **map_lines, t_context *ctx)
{
	int x;
	int y;
	int player_count;

	player_count = 0;
	y = 0;
	while (map_lines[y])
	{
		x = 0;
		if (ft_strlen(map_lines[y]) == 0 || is_blank_line(map_lines[y]) == 1)
			return (write_error("Error: empty line in map\n"));
		while (map_lines[y][x])
		{
			if (is_allowed_map_char(map_lines[y][x]) == 0)
				return (write_error("Error: invalid character in map\n"));
			if (map_lines[y][x] == 'N' || map_lines[y][x] == 'S'
				|| map_lines[y][x] == 'E' || map_lines[y][x] == 'W')
			{
				ctx->map.player_x = x;
				ctx->map.player_y = y;
				ctx->map.player_dir = map_lines[y][x];
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (write_error("Error: there must be exactly one player in the map\n"));
	return (1);
}