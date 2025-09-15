/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_int_from_stdin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:38:52 by abonifac          #+#    #+#             */
/*   Updated: 2025/09/15 17:03:44 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_noleak.h"
#include <unistd.h>
#include "libft.h"
#include "mapgen.h"

int	read_int_from_stdin(const char *prompt)
{
	char	*line;
	int		value;

	while (1)
	{
		write(2, GREEN, ft_strlen(RED));
		write(2, BOLD, ft_strlen(BOLD));
		write(2, prompt, ft_strlen(prompt));
		write(2, RESET, ft_strlen(RESET));
		line = gnl_noleak(0);
		if (!line)
		{
			write(2, "EOF received\n", 13);
			exit(1);
		}
		value = ft_atoi(line);
		free(line);
		if (value >= 3 && value <= 500)
			return (value);
		write(2, "Value must be between 3 and 500\n", 32);
	}
}
