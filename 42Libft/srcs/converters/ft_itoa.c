/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:06:31 by tlutz             #+#    #+#             */
/*   Updated: 2025/01/27 19:03:54 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*result;	
	int			count;
	long int	nbr;

	nbr = n;
	count = count_numbers(n);
	if (n < 0)
	{
		nbr *= -1;
		count++;
	}
	result = (char *)malloc (sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = '\0';
	while (count-- > 0)
	{
		result[count] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
