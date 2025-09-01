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

int	ft_strlen_less_char(char *s, char c)
{
	int i;
	int	count;

	if (s == NULL)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
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
	len = ft_strlen_less_char(value, ' ');
	new_value = malloc(sizeof(char) * (len + 1));
	if (new_value == NULL)
		return (NULL);
	new_value[len] = '\0';
	i = 0;
	len = 0;
	while (new_value[i])
	{
		if (is_space_or_tab(value[i]))
		{
			i++;
			continue ;
		}
		new_value[len] = value[i];
		len++;
		i++;
	}
	free(value);
	return (new_value);
}

int	parse_color_line(int dst[3], char *value)
{
	int	i;

	i = 0;
	value = remove_spaces(value);
	if (parse_rgb(value, &i, &dst[0]) == 0)
		return (0);
	if (value[i] != ',')
		return (write_error("Error: separator must be a coma ','\n"));
	i++;
	if (parse_rgb(value, &i, &dst[1]) == 0)
		return (0);
	if (value[i] != ',')
		return (write_error("Error: separator must be a coma ','\n"));
	i++;
	if (parse_rgb(value, &i, &dst[2]) == 0)
		return (0);
	i = skip_spaces(value, i);
	if (value[i] != '\0')
		return (write_error("Error: respect line format for floor and ceil\n"));
	return (1);
}