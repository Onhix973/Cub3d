/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:09:53 by tlutz             #+#    #+#             */
/*   Updated: 2024/12/12 19:11:21 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*handle_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*tmp;

	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (handle_free(&stash));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		handle_free(&stash);
		if (!tmp)
			return (NULL);
		stash = tmp;
	}
	return (stash);
}

static char	*reset_stash(char *stash, char *nl)
{
	char	*tmp;

	tmp = ft_strdup(nl + 1);
	handle_free(&stash);
	if (!tmp)
		return (NULL);
	stash = tmp;
	return (stash);
}

static char	*get_line_from_stash(char **stash)
{
	char	*line;
	char	*nl;

	line = NULL;
	nl = ft_strchr(*stash, '\n');
	if (!nl)
	{
		if (**stash)
			line = ft_strdup(*stash);
		handle_free(stash);
		return (line);
	}
	line = ft_substr(*stash, 0, nl - *stash + 1);
	if (!line)
		return (handle_free(stash));
	*stash = reset_stash(*stash, nl);
	if (!*stash)
		return (handle_free(&line));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line_from_stash(&stash);
	return (line);
}
