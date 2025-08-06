/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:54:48 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/24 11:46:15 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(str);
	while (i < strlen + 1)
	{
		if (str[i] == (char)c)
			return ((char *)(&str[i]));
		i++;
	}
	return (0);
}
