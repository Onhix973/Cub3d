#include "parsing.h"
#include <stdlib.h>

/*
 * Return the last word without any space
*/
int	extract_value_after_key(const char *line, char *key, char **out)
{
	int		i;
	char	*trimmed;

	*out = NULL;
	if (check_first_word(line, key) == 0)
		return (0);
	i = 0;
	while (key[i])
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

int	fill_color_helper(int key, char *str, const char *line, t_config *conf)
{
	char	*val;

	val = NULL;
	if (conf->seen[key] == 1)
		return (write_error("Error:\nduplicate directive\n"));
	if (extract_value_after_key(line, str, &val) != 1)
		return (0);
	if (key == FLOOR || key == CEIL)
	{
		if (parse_color_line(conf->floor, val) != 1)
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
