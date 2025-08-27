/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:37:54 by tlutz             #+#    #+#             */
/*   Updated: 2025/03/17 14:49:45 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/**
 * @brief A simple implmentation of the printf function that writes
 * to the standard output.
 * 
 * Supports "%i, %d , %s, %c, %x, %X ,%p, %u" flags.
 * 
 * @param format A string that specifies how subsequent arguments are converted.
 * @param ... (Additional arguments).
 * @return On success, the total number of characters written is returned.
 * On failure, a negative number is returned.
 */
int		ft_printf(const char *format, ...);

int		ft_putchar_fd(char c, int fd);

int		ft_putstr_fd(char *s, int fd);

int		ft_putptr(void *ptr);

size_t	ft_strlen(const char *str);

int		ft_putnbr_base(int n, int fd, char *base);

int		ft_uputnbr_base(unsigned int n, int fd, char *base);

void	ft_write_number(unsigned long int nb, int fd, int *count, char *base);

#endif