/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 13:31:33 by santa             #+#    #+#             */
/*   Updated: 2019/10/01 15:49:29 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			t_flags_new(t_flags *res)
{
	res->sharp = 0;
	res->zero = 0;
	res->plus = 0;
	res->minus = 0;
	res->space = 0;
	res->h = 0;
	res->hh = 0;
	res->l = 0;
	res->ll = 0;
	res->ld = 0;
}

static t_printf	*t_printf_new(t_printf *res)
{
	t_flags_new(res->flags);
	res->taille_mini = 0;
	res->precision = -1;
	res->size = 0;
	res->conversion = 0;
	return (res);
}

static void		ft_printf_options(t_printf *to_print, va_list *ap)
{
	if (to_print->conversion == '%' || to_print->conversion == 'c')
		ft_print_chr(to_print, ap);
	else if (to_print->conversion == 's')
		ft_print_str(to_print, ap);
	else if (to_print->conversion == 'p')
		ft_print_ptr(to_print, ap);
	else if (to_print->conversion == 'o')
		ft_print_octal(to_print, ap);
	else if (to_print->conversion == 'x' || to_print->conversion == 'X')
		ft_print_hexa(to_print, ap);
	else if (to_print->conversion == 'u')
		ft_print_unsigned(to_print, ap);
	else if (to_print->conversion == 'd' || to_print->conversion == 'i')
		ft_print_integer(to_print, ap);
	else if (to_print->conversion == 'f')
		ft_print_fl(to_print, ap);
	else if (to_print->conversion == 'b')
		ft_print_bin(to_print, ap);
}

static void		ft_printf2(const char **format, t_printf *to_print,
	int *res, va_list *ap)
{
	to_print = t_printf_new(to_print);
	to_print = parse_printf(format, to_print, ap);
	ft_printf_options(to_print, ap);
	*res += to_print->size;
}

int				ft_printf(const char *format, ...)
{
	t_printf	*to_print;
	va_list		ap;
	int			res;

	if (!format || !(to_print = (t_printf*)malloc(sizeof(t_printf)))
		|| !(to_print->flags = (t_flags*)malloc(sizeof(t_flags))))
		exit(1);
	res = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format && *format == '{')
			res = ft_color((char **)&format, res);
		if (*format && *format != '%')
			res += write(1, format++, 1);
		else if (*format && *(++format))
			ft_printf2(&format, to_print, &res, &ap);
	}
	free(to_print);
	free(to_print->flags);
	va_end(ap);
	return (res);
}
