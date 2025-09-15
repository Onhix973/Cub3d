/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:41:39 by abonifac          #+#    #+#             */
/*   Updated: 2025/08/27 14:39:04 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_noleak.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static char	*handle_eof(char *line, ssize_t read_bytes)
{
	if (line[0] == '\0' || read_bytes == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static ssize_t	read_to_buffer(int fd, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*update_line(char *line, char *buffer)
{
	char	*new_lpos;
	char	*tmp;
	ssize_t	line_lenght;

	new_lpos = ft_strchr(buffer, '\n');
	line_lenght = ft_strlen(line);
	if (new_lpos)
	{
		tmp = strjoin_gnl(line, buffer, line_lenght, new_lpos - buffer + 1);
		free(line);
		if (!tmp)
			return (NULL);
		line = tmp;
		ft_strcpy(buffer, new_lpos + 1);
	}
	else
	{
		tmp = strjoin_gnl(line, buffer, line_lenght, ft_strlen(buffer));
		free(line);
		if (!tmp)
			return (NULL);
		line = tmp;
		buffer[0] = '\0';
	}
	return (line);
}

char	*gnl_noleak(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read_to_buffer(fd, buffer);
			if (bytes_read <= 0)
				return (handle_eof(line, bytes_read));
		}
		line = update_line(line, buffer);
		if (!line || ft_strchr(line, '\n'))
			return (line);
	}
}
