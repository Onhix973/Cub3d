/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:59:26 by abonifac          #+#    #+#             */
/*   Updated: 2025/08/27 14:38:40 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*strjoin_gnl(char *s1, char const *s2, ssize_t len_s1, ssize_t len_s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif