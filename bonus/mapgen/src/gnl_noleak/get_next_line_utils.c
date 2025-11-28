/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:56:16 by abonifac          #+#    #+#             */
/*   Updated: 2025/08/18 14:32:40 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char	*strjoin_gnl(char *s1, char const *s2, ssize_t len_s1, ssize_t len_s2)
{
	char		*str;
	ssize_t		index_s1;
	ssize_t		index_s2;

	index_s1 = -1;
	index_s2 = -1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (++index_s1 < len_s1)
		str[index_s1] = s1[index_s1];
	while ((++index_s2 < len_s2))
	{
		str[index_s1 + index_s2] = s2[index_s2];
		if (s2[index_s2] == '\n')
			break ;
	}
	if (s2[index_s2] == '\n')
		str[index_s1 + index_s2++] = '\n';
	str[index_s1 + index_s2] = '\0';
	return (str);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
