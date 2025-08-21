
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
	char *dup;
	int i;
	int	len;

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

/*
	we want a tab that has as many separator
*/
char **split_with_sep(char const *line, char sep)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	tab = malloc(sizeof(char *) * (count_all_fields(line, sep) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == sep)
		{
			tab[j] = dup_string(line, start, i);
			if (tab[j] == NULL)
				return (free_tab(tab, j - 1));
			j++;
			start = i + 1;
		}
		i++;
	}
	tab[j] = dup_string(line, start, i);
	if (tab[j] == NULL)
		return (free_tab(tab, j - 1));
	j++;
	tab[j] = NULL;
	return (tab);
}
