/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:53:42 by abonifac          #+#    #+#             */
/*   Updated: 2025/12/03 23:14:07 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

int	parse_rgb(const char *s, int *i, int *out)
{
	long	value;
	int		decimal;
	int		y;

	y = 0;
	if (s[*i] < '0' || s[*i] > '9')
		return (write_error(RGB_FMT_ERR));
	value = 0;
	while (s[*i] == '0')
		*i = *i + 1;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		decimal = s[*i] - '0';
		value = value * 10 + decimal;
		*i = *i + 1;
		y++;
	}
	if (value > 255 || y > 10)
		return (write_error("Error:\nRGB value must be <= 255\n"));
	*out = value;
	return (1);
}

int	ft_strlen_less_spaces(char *s)
{
	int	i;
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

int	return_free_with_error(char *s, int (*write_error)(const char *)
	, const char *msg)
{
	if (s)
		free(s);
	return (write_error(msg));
}

int	parse_color_line(int dst[3], char *value)
{
	char	*clean;
	int		i;

	i = 0;
	clean = remove_spaces(value);
	if (clean == NULL)
		return (write_error(MALLOC_ERR));
	if (parse_rgb(clean, &i, &dst[0]) == 0)
		return (return_free_with_error(clean, write_error, ""));
	if (clean[i] != ',')
		return (return_free_with_error(clean, write_error, RGB_FMT_ERR));
	i++;
	if (parse_rgb(clean, &i, &dst[1]) == 0)
		return (return_free_with_error(clean, write_error, ""));
	if (clean[i] != ',')
		return (return_free_with_error(clean, write_error, RGB_FMT_ERR));
	i++;
	if (parse_rgb(clean, &i, &dst[2]) == 0)
		return (return_free_with_error(clean, write_error, ""));
	i = skip_spaces(clean, i);
	if (clean[i] != '\0')
		return (return_free_with_error(clean, write_error, RGB_FMT_ERR));
	free(clean);
	return (1);
}
