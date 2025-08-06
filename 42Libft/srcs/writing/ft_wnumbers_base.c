/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wnumbers_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:22:29 by tlutz             #+#    #+#             */
/*   Updated: 2024/12/04 17:27:39 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_number(unsigned long int nb, int fd, int *count, char *base)
{
	size_t	len_base;

	len_base = ft_strlen(base);
	if (nb >= len_base)
		ft_write_number((nb / len_base), fd, count, base);
	if (write (fd, &base[nb % len_base], 1) == -1)
	{
		*count = -1;
		return ;
	}
	(*count)++;
}
