/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:49:02 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/24 11:46:10 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_number(unsigned int nb, int fd)
{
	if (nb > 9)
		ft_write_number((nb / 10), fd);
	write (fd, &"0123456789"[nb % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	nbr = (unsigned int) n;
	ft_write_number(nbr, fd);
}
