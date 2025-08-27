/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:28:27 by tlutz             #+#    #+#             */
/*   Updated: 2025/01/27 14:47:22 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		return (ft_putstr_fd("(nil)", 1));
	if (ft_putstr_fd("0x", 1) == -1)
		return (-1);
	count += 2;
	ft_write_number((unsigned long)ptr, 1, &count, "0123456789abcdef");
	return (count);
}
