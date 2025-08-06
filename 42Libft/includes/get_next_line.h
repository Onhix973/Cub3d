/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:09:51 by tlutz             #+#    #+#             */
/*   Updated: 2025/03/17 14:54:56 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 150
# endif

# include <stdlib.h>
# include <unistd.h>

/**
 * @brief Reads an return the next line from a file descriptor.
 * 
 * This function reads from the given file descriptor and returns the next line,
 * including the newline character if present. It uses a static variable to
 * maintain state between function calls, allowing it to read files line by line
 * 
 * @param fd The file descriptor to read from.
 * @return A pointer to the line read from the file, or NULL if there's nothing
 * more to read or if an error occured.
 * 
 * @note The returned line should be freed by the caller when no longer needed.
 * The function handles reading with a buffer, the szie of wich can be defined
 * at compile time with -D BUFFER_SIZE=n.
 */
char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strdup(const char *src);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strchr(const char *str, int c);

#endif