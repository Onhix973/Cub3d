#include "parsing.h"
#include <stdlib.h>
#include "libft.h"
#include "gnl_noleak.h"

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
	return (1);
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
	if (read_file(fd, &buf) == 0)
		return (write_error("Error reading file\n"));
	lines = split_with_sep(buf, '\n');
	free(buf);
	if (lines == NULL)
		return (write_error("Error splitting lines\n"));
	*out_lines = lines;
	return (1);
}


////////////////////////////


int	check_first_word(const char *line, char *key)
{
	int i;

	i = 0;
	while (key[i] != '\0')
	{
		if (line[i] != key[i])
			return (0);
		i++;
	}
	if (!is_space_or_tab(line[i]))
		return (0);
	return (1);
}


/*
 * Return the last word without any space
*/
char *dup_last_word(const char *s)
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
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}


int extract_value_after_key(const char *line, char *key, char **out)
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

int	fill_texture_helper(int key, char *str, const char *line, t_config *conf)
{
	char	*val;

	val = NULL;
	if (conf->seen[key] == 1)
		return (write_error("Error: duplicate directive\n"));
	if (extract_value_after_key(line, str, &val) != 1)
	{
		free(val);
		return (0);
	}
	conf->path[key] = val;
	conf->seen[key] = 1;
	return (1);
}

int fill_color_helper(int key, char *str, const char *line, t_config *conf)
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
			if (val)
				free(val);
			return (0);
		}
	}
	else if (key == CEIL)
	{
		if (parse_color_line(conf->ceil, val) != 1)
		{
			if (val)
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
		return (fill_texture_helper(NO, "NO", line, conf));
	else if (check_first_word(line, "SO"))
		return (fill_texture_helper(SO, "SO", line, conf));
	else if (check_first_word(line, "WE"))
		return (fill_texture_helper(WE, "WE", line, conf));
	else if (check_first_word(line, "EA"))
		return (fill_texture_helper(EA, "EA", line, conf));
	else if (check_first_word(line, "F"))
		return (fill_color_helper(FLOOR, "F", line, conf));
	else if (check_first_word(line, "C"))
		return (fill_color_helper(CEIL, "C", line, conf));
	return (write_error("Error: invalid input header\n"));

}

// Check if the line is a valid directive and fill the config struct

int	check_directives(const char *line, t_config *conf)
{
	int res;

	res = fill_texture(conf, line);
	if (res != 1)
		return (res);
	return (1);
}

int all_seen(t_config *config)
{
	int i;
	
	i = 0;
	while (i < NB_OF_MAP_PARAMS)
	{
		if (config->seen[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int parse_header(char **lines, t_config *conf)
{
	int	i;
	int res;

	i = 0;
	while (lines[i] && all_seen(conf) == 0)
	{
		if (is_blank_line(lines[i]) == 1)
			i++;
		else
		{
			res = check_directives(lines[i], conf);
			if (res == 0)
				return (write_error("Error: unexpected content before map\n"));
			i++;
		}
	}
	if (all_seen(conf) == 0)
		return (write_error("Error: not all directives seen\n"));
	while (lines[i] && is_blank_line(lines[i]) == 1)
		i++;
	if (lines[i] == NULL)
		return (write_error("Error: no map found\n"));
	conf->i_map_start = i;
	return (1);
}