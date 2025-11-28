/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:10:06 by abonifac          #+#    #+#             */
/*   Updated: 2025/09/15 17:39:02 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"
#include <stdlib.h>
#include <unistd.h>

int	convert_args(char **av, int ac, t_mapgen *config)
{
	if (ac == 3)
	{
		config->width = atoi(av[1]);
		config->height = atoi(av[2]);
		if (config->width <= 0 || config->height <= 0)
			return (write_error(ARGS_ERR));
		if (config->width >= 1000 || config->height >= 1000)
			return (write_error("Error:\nYou fool\n"));
	}
	else
	{
		write(2, "Enter map dimensions\n", 22);
		write(2, "Square map between 10/100 recommended\n", 38);
		config->width = read_int_from_stdin("Width:\n");
		config->height = read_int_from_stdin("Height:\n");
	}
	return (1);
}
