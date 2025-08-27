/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:14:49 by tlutz             #+#    #+#             */
/*   Updated: 2025/01/27 14:47:01 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	len_s;

	if (!s)
		return (ft_putstr_fd("(null)", 1));
	len_s = ft_strlen(s);
	return (write (fd, s, len_s));
}
