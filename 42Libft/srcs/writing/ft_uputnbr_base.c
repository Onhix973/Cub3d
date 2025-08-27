/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:33:16 by tlutz             #+#    #+#             */
/*   Updated: 2024/12/04 17:30:26 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uputnbr_base(unsigned int n, int fd, char *base)
{
	unsigned int	nbr;
	int				count;

	count = 0;
	nbr = n;
	ft_write_number(nbr, fd, &count, base);
	return (count);
}
