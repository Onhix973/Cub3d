/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:53:36 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/28 15:53:38 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing.h"
#include "libft.h"

int	check_first_word(const char *line, char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (line[i] != key[i])
			return (0);
		i++;
	}
	if (!is_space_or_tab(line[i]))
		return (0);
	return (1);
}

/* receive an argument &s[i] so it might not start from the beginning */
char	*dup_last_word(const char *s)
{
	int		start;
	int		end;
	int		i;
	char	*dst;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] && is_space_or_tab(s[start]) == 1)
		start++;
	end = ft_strlen(s);
	if (end > 0)
		end--;
	while (end >= start && is_space_or_tab(s[end]) == 1)
		end--;
	dst = malloc(sizeof(char) * (end - start + 2));
	if (dst == NULL)
		return (NULL);
	i = -1;
	while ((start + ++i) <= end)
		dst[i] = s[start + i];
	dst[i] = '\0';
	return (dst);
}
