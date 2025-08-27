/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:04:12 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/25 18:13:27 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		index_s;
	size_t		index_e;
	char		*dest;

	if (!s1 || !set)
		return (0);
	index_s = 0;
	index_e = ft_strlen(s1);
	while (s1[index_s] && ft_strchr(set, s1[index_s]))
		index_s++;
	while (index_e > 0 && ft_strchr(set, s1[index_e]))
		index_e--;
	dest = ft_substr(s1, index_s, (index_e - index_s) + 1);
	return (dest);
}
