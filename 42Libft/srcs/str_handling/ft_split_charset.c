/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:24:37 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/09 17:34:23 by tlutz            ###   ########.fr       */
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

static int	is_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	word_count(char const *s, const char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_charset(s[i], charset))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !is_charset(s[i], charset))
				i++;
		}
	}
	return (count);
}

static int	get_len_word(const char *s, const char *charset)
{
	int	len_word;

	len_word = 0;
	while (s[len_word] && !is_charset(s[len_word], charset))
		len_word++;
	return (len_word);
}

char	**ft_split_charset(char const *s, const char *charset)
{
	char	**dest;
	int		j;

	j = 0;
	if (!s || !charset)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (word_count(s, charset) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		while (*s && is_charset(*s, charset))
			s++;
		if (*s)
		{
			dest[j] = ft_strndup(s, get_len_word(s, charset));
			if (!dest[j])
				return (free_dest(dest, j - 1));
			s += get_len_word(s, charset);
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}
