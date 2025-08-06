/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:46:29 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/25 18:20:34 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*src2;
	char		*dest2;

	i = n;
	src2 = (const char *)src;
	dest2 = (char *)dest;
	if (dest2 <= src2)
		return (ft_memcpy(dest2, src2, n));
	while (i > 0)
	{
		(dest2)[i - 1] = (src2)[i - 1];
		i--;
	}
	return (dest);
}
