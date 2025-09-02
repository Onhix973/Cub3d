/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:37 by abonifac          #+#    #+#             */
/*   Updated: 2025/09/02 15:19:18 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_isspaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int is_space_or_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int is_blank_line(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (!ft_isspaces(s[i]))
			return(0);
		i++;
	}
	return 1;
}

int skip_spaces(const char *s, int i)
{
	while (s[i] && is_space_or_tab(s[i] == 1))
		i++;
	return (i);
}