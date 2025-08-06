/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:01:04 by tlutz             #+#    #+#             */
/*   Updated: 2024/11/24 11:46:14 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_dest(char **dest, int j)
{
	while (j >= 0)
	{
		free(dest[j]);
		j--;
	}
	free(dest);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static int	get_len_word(const char *s, char c)
{
	int	len_word;

	if (!ft_strchr(s, c))
		len_word = ft_strlen(s);
	else
		len_word = ft_strchr(s, c) - s;
	return (len_word);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		j;

	j = 0;
	dest = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			dest[j] = ft_substr(s, 0, get_len_word(s, c));
			if (!dest[j])
				return (free_dest(dest, j - 1));
			s += get_len_word(s, c);
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}
