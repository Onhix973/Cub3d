/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:19:03 by tlutz             #+#    #+#             */
/*   Updated: 2024/12/04 17:29:18 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int n, int fd, char *base)
{
	unsigned int	nbr;
	int				count;

	count = 0;
	if (n < 0 && ft_strlen(base) == 10)
	{
		write(fd, "-", 1);
		n = -n;
		count++;
	}
	nbr = (unsigned int) n;
	ft_write_number(nbr, fd, &count, base);
	return (count);
}
