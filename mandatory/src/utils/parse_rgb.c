/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:53:42 by abonifac          #+#    #+#             */
/*   Updated: 2025/12/04 16:34:03 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static int	look_for_spaces(const char *s, int i)
{
	int	y;

	if (!ft_isspaces(s[i]))
		return (1);
	y = i;
	while (ft_isspaces(s[y]))
		y++;
	if (s[y] >= '0' && s[y] <= '9')
		return (0);
	return (1);
}

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
	if (look_for_spaces(s, *i) == 0)
		return (write_error(RGB_FMT_ERR));
	*out = value;
	return (1);
}

int	parse_color_line(int dst[3], char *value)
{
	int	i;

	i = 0;
	i = skip_spaces(value, i);
	if (parse_rgb(value, &i, &dst[0]) == 0)
		return (0);
	i = skip_spaces(value, i);
	if (value[i] != ',')
		return (write_error(RGB_FMT_ERR));
	i++;
	i = skip_spaces(value, i);
	if (parse_rgb(value, &i, &dst[1]) == 0)
		return (0);
	i = skip_spaces(value, i);
	if (value[i] != ',')
		return (write_error(RGB_FMT_ERR));
	i++;
	i = skip_spaces(value, i);
	if (parse_rgb(value, &i, &dst[2]) == 0)
		return (0);
	i = skip_spaces(value, i);
	if (value[i] != '\0')
		return (write_error(RGB_FMT_ERR));
	return (1);
}
