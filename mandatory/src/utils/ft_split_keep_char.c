/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:53:12 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/28 15:53:13 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	*free_tab(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

static int	count_all_fields(const char *str, char c)
{
	int	i;
	int	count;

	if (str == NULL)
		return (0);
	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static char	*dup_string(char const *line, int start, int pos)
{
	char	*dup;
	int		i;
	int		len;

	len = pos - start;
	i = 0;
	dup = malloc(sizeof(char *) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = line[start + i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**fill_tab(char **tab, int j, char *str, char sep)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			tab[j] = dup_string(str, start, i);
			if (tab[j] == NULL)
				return (free_tab(tab, j - 1));
			j++;
			start = i + 1;
		}
		i++;
	}
	tab[j] = dup_string(str, start, i);
	if (tab[j] == NULL)
		return (free_tab(tab, j - 1));
	j++;
	tab[j] = NULL;
	return (tab);
}

/*
	we want a tab that has as many separator
*/
char	**split_with_sep(char const *line, char sep)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (count_all_fields(line, sep) + 1));
	if (tab == NULL)
		return (NULL);
	tab = fill_tab(tab, 0, (char *)line, sep);
	if (tab == NULL)
		return (NULL);
	return (tab);
}
