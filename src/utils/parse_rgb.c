#include "parsing.h"
#include <stdlib.h>

int	parse_rgb(const char *s, int *i, int *out)
{
	int value;
	int	decimal;
	
	if (s[*i] < '0' || s[*i] > '9')
		return (write_error("Error: RGB format\n"));
	value = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		decimal = s[*i] - '0';
		value = value * 10 + decimal;
		*i = *i + 1;
	}
	if (value > 255)
		return (write_error("Error: RGB value must be <= 255\n"));
	*out = value;
	return (1);
}

int	ft_strlen_less_spaces(char *s)
{
	int i;
	int	count;

	if (s == NULL)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (is_space_or_tab(s[i]) == 0)
			count++;
		i++;
	}
	return (count);
}

char  *remove_spaces(char *value)
{
	int len;
	int i;
	char *new_value;

	i = 0;
	len = ft_strlen_less_spaces(value);
	new_value = malloc(sizeof(char) * (len + 1));
	if (new_value == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (value[i])
	{
		if (is_space_or_tab(value[i]) == 0)
		{
			new_value[len] = value[i];
			len++;
		}
		i++;
	}
	new_value[len] = '\0';
	return (new_value);
}

int	parse_color_line(int dst[3], char *value)
{
	char *clean;
	int	i;
	int err;

	i = 0;
	err = 0;
	clean = remove_spaces(value);
	if (clean == NULL)
		return (write_error("Error: malloc failed\n"));
	if (parse_rgb(clean, &i, &dst[0]) == 0)
		err = 1;
	if (clean[i] != ',')
		err = 2;
	i++;
	if (parse_rgb(clean, &i, &dst[1]) == 0)
		err = 1;
	if (clean[i] != ',')
		err = 2;
	i++;
	if (parse_rgb(clean, &i, &dst[2]) == 0)
		err = 1;
	i = skip_spaces(clean, i);
	if (clean[i] != '\0')
		return (write_error("Error: respect line format for floor and ceil\n"));
	free(clean);
	if (err != 0)
		return (write_error("Error: RGB format\n"));
	return (1);
}