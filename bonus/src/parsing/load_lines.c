/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:54:15 by abonifac          #+#    #+#             */
/*   Updated: 2025/11/28 15:54:16 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"

static int	read_file(int fd, char **out_buf)
{
	char	*acc;
	char	*line;

	*out_buf = NULL;
	acc = (char *)malloc(1);
	if (!acc)
		return (write_error(MALLOC_ERR));
	acc[0] = '\0';
	line = get_next_line(fd);
	while (line)
	{
		acc = ft_strjoin_re(acc, line);
		free(line);
		if (!acc)
			return (write_error(MALLOC_ERR));
		line = get_next_line(fd);
	}
	*out_buf = acc;
	return (1);
}

int	load_lines(int fd, char ***out_lines)
{
	char	*buf;
	char	**lines;

	*out_lines = NULL;
	if (read_file(fd, &buf) == 0)
		return (0);
	lines = split_with_sep(buf, '\n');
	free(buf);
	if (lines == NULL)
		return (write_error("Error:\nsplitting lines\n"));
	*out_lines = lines;
	return (1);
}
