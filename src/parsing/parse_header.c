#include "parsing.h"
#include <stdlib.h>
#include "libft.h"
#include "gnl_noleak.h"

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
				return (0);
			i++;
		}
	}
	if (all_seen(conf) == 0)
		return (write_error("Error: not all directives seen\n"));
	while (lines[i] && is_blank_line(lines[i]) == 1)
		i++;
	if (lines[i] && check_directives(lines[i], conf) == 1)
		return (0);
	if (lines[i] == NULL)
		return (write_error("Error: no map found\n"));
	conf->i_map_start = i;
	return (1);
}