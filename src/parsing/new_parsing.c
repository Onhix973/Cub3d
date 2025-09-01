#include "parsing.h"
#include <stdlib.h>
#include "libft.h"
#include "gnl_noleak.h"

void	ft_free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}




void config_free(t_config *c)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (c->path[i] != NULL)
			free(c->path[i]);
		i++;
	}
}

void map_free(t_map *m)
{
	int i;

	if (m->grid == NULL)
		return ;
	i = 0;
	while (i < m->height)
	{
		if (m->grid[i] != NULL)
			free(m->grid[i]);
		i++;
	}
	free(m->grid);
	map_init(m);
}

void context_free(t_context *ctx)
{
	map_free(&ctx->map);
	config_free(&ctx->conf);
	ft_free_split(ctx->lines);
	ctx->lines = NULL;
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

int	read_file(int fd, char **out_buf)
{
	char *acc;
	char *line;

	*out_buf = NULL;
	acc = (char *)malloc(1);
	if (!acc)
		return (write_error("Malloc error\n"));
	acc[0] = '\0';
	line = gnl_noleak(fd);
	while (line)
	{
		acc = ft_strjoin_re(acc, line);
		free(line);
		if (!acc)
			return (write_error("Malloc error\n"));
		line = gnl_noleak(fd);
	}
	*out_buf = acc;
	return (0);
}

int	count_fields(const char *s, char c)
{
	int	i;
	int	count;

	if (s == NULL)
		return (0);
	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	load_lines(int fd, char ***out_lines)
{
	char *buf;
	char	**lines;

	*out_lines = NULL;
	if (read_file(fd, &buf) != 0)
		return (write_error("Error reading file\n"));
	lines = split_with_sep(buf, '\n');
	free(buf);
	if (lines == NULL)
		return (write_error("Error splitting lines\n"));
	*out_lines = lines;
	return (0);
}


////////////////////////////


int	check_first_word(char *line, char *key)
{
	int i;

	i = 0;
	while (key[i] != '\0')
	{
		if (line[i] != key[i])
		{
			return (write_error("Invalid key for header\n"));
		}
		i++;
	}
	if (!ft_is_space_or_tab(line[i]))
		return (write_error("Invalid entry for header\n"));
	return (1);
}


/*
 * Return the last word without any space
*/
char *dup_last_word(char *s)
{
	int	start;
	int	end;
	int	i;
	char	*dst;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] && is_space_or_tab(s[start]) == 1)
		start++;
	end = ft_strlen(s);
	if (end > 0)
		end--;
	while (end >= start && is_space_or_tab(s[end]) == 1)
		end--;
	dst = malloc(sizeof(char) * (end - start + 2));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		dst[i] == s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}


int extract_value_after_key(char *line, char *key, char **out)
{
	int	i;
	char	*trimmed;

	*out = NULL;
	if (check_first_word(line, key) == 0)
		return (0);
	i = 0;
	while(key[i])
		i++;
	i = skip_spaces(line, i);
	if (line[i] == '\0')
		return (write_error("Error: missing value after key\n"));
	trimmed = dup_last_word(&line[i]);
	if (trimmed == NULL)
		return (write_error("Error: malloc failed\n"));
	*out = trimmed;
	return (1);
}

int	fill_texture_helper(int key, char *str, char *line, t_config *conf)
{
	char	*val;

	val = NULL;
	if (conf->seen[key] == 1)
		return (write_error("Error: duplicate directive\n"));
	if (extract_value_after_key(line, str, &val) != 1)
		return (0);
	conf->path[0] = val;
	conf->seen[NO] = 1;
	return (1);
}

int fill_color_helper(int key, char *str, char *line, t_config *conf)
{
	char	*val;

	val = NULL;
	if (conf->seen[key] == 1)
		return (write_error("Error: duplicate directive\n"));
	if (extract_value_after_key(line, str, &val) != 1)
		return (0);
	if (key == FLOOR)
	{
		if (parse_color_line(conf->floor, val) != 1)
		{
			free(val);
			return (0);
		}
	}
	else if (key == CEIL)
	{
		if (parse_color_line(conf->ceil, val) != 1)
		{
			free(val);
			return (0);
		}
	}
	free(val);
	conf->seen[key] = 1;
	return (1);
}

int	fill_texture(t_config *conf, const char *line)
{
	if (check_first_word(line, "NO"))
		fill_texture_helper(NO, "NO", line, conf);
	else if (check_first_word(line, "SO"))
		fill_texture_helper(SO, "SO", line, conf);
	else if (check_first_word(line, "WE"))
		fill_texture_helper(WE, "WE", line, conf);
	else if (check_first_word(line, "EA"))
		fill_texture_helper(EA, "EA", line, conf);
	else if (check_first_word(line, "F"))
		fill_color_helper(FLOOR, "F", line, conf);
	else if (check_first_word(line, "C"))
		fill_color_helper(CEIL, "C", line, conf);
	else if (check_first_word(line, "\0"))
		return (1);
	else
		return (write_error("Error: invalid input header\n"));
}