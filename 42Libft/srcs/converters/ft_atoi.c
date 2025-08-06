/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:40:36 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/25 00:53:32 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_white_spaces(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	return (i);
}

static int	ft_sign(const char *nptr, int i, int *sign)
{
	if (nptr[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
	{
		*sign = 1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			j;
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	j = ft_white_spaces(nptr);
	j = ft_sign(nptr, j, &sign);
	while (ft_isdigit(nptr[j]))
	{
		if (result != ((result * 10) + (nptr[j] - 48)) / 10)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		result = result * 10 + (nptr[j] - 48);
		j++;
	}
	return (result * sign);
}
