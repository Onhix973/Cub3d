/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:00:29 by tlutz             #+#    #+#             */
/*   Updated: 2025/01/14 18:33:53 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(const char format, va_list args)
{
	int	count;

	count = 0;
	if (format == 'i' || format == 'd')
		count = (ft_putnbr_base(va_arg(args, int), 1, "0123456789"));
	else if (format == 's')
		count = (ft_putstr_fd(va_arg(args, char *), 1));
	else if (format == 'x')
		count = (ft_uputnbr_base(va_arg(args, unsigned int), 1, \
		"0123456789abcdef"));
	else if (format == 'X')
		count = (ft_uputnbr_base(va_arg(args, unsigned int), 1, \
		"0123456789ABCDEF"));
	else if (format == 'c')
		count = (ft_putchar_fd(va_arg(args, int), 1));
	else if (format == 'p')
		count = (ft_putptr(va_arg(args, void *)));
	else if (format == 'u')
		count = (ft_uputnbr_base(va_arg(args, unsigned int), 1, "0123456789"));
	else if (format == '%')
		count = (ft_putchar_fd('%', 1));
	else
		count = (ft_putchar_fd(format, 1));
	return (count);
}

static int	printf_handler(const char *format, int len_printed, va_list args)
{
	int	i;
	int	check;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i])
				check = handle_format(format[i], args);
			else
				return (-1);
		}
		else
			check = ft_putchar_fd(format[i], 1);
		if (check == -1)
			return (-1);
		len_printed += check;
		i++;
	}
	return (len_printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len_printed;

	len_printed = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	len_printed = printf_handler(format, len_printed, args);
	va_end(args);
	return (len_printed);
}
