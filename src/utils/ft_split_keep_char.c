/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:45:24 by abonifac          #+#    #+#             */
/*   Updated: 2025/08/20 17:52:57 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	*free_tab(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

int	count_all_fields(const char *str, char c)
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

/*
	we want a tab that has as many separator
*/
char **split_with_sep(char const *line, char *sep)
{
	char	**tab;
	int		i;
	int		j;

	tab = malloc(sizeof(char *) * count_all_fields(line, sep) + 1);
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == sep)
		{
			tab[j] = ;
		}
	}
	
}