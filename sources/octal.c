/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 06:50:50 by santa             #+#    #+#             */
/*   Updated: 2019/10/01 10:43:53 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*handle_octal_precision(t_printf *to_print, char *octal)
{
	if (to_print->precision == 0 && *octal == '0')
	{
		ft_strdel(&octal);
		EXIT_IF_FAIL((octal = ft_strnew(0)));
		if (to_print->flags->sharp)
			EXIT_IF_FAIL((octal = ft_strjoin_free("0", octal, 2)));
		return (octal);
	}
	to_print->flags->sharp && *octal != '0'
		? octal = ft_strjoin_free("0", octal, 2) : 0;
	EXIT_IF_FAIL(octal);
	if (to_print->precision > 0)
		while (ft_strlen(octal) < (unsigned)to_print->precision)
			EXIT_IF_FAIL((octal = ft_strjoin_free("0", octal, 2)));
	return (octal);
}

static void	ft_print_octal2(t_printf *to_print, va_list *ap, char **octal)
{
	if (to_print->flags->h)
		EXIT_IF_FAIL((*octal = ft_utoa_base(
			(unsigned short)va_arg(*ap, unsigned), 8)));
	else if (to_print->flags->hh)
		EXIT_IF_FAIL((*octal = ft_utoa_base(
			(unsigned char)va_arg(*ap, unsigned), 8)));
	else if (to_print->flags->l)
		EXIT_IF_FAIL((*octal = ft_ultoa_base(va_arg(*ap, unsigned long), 8)));
	else if (to_print->flags->ll)
		EXIT_IF_FAIL((*octal = ft_ulltoa_base(
			va_arg(*ap, unsigned long long), 8)));
	else
		EXIT_IF_FAIL((*octal = ft_utoa_base(va_arg(*ap, unsigned), 8)));
}

void		ft_print_octal(t_printf *to_print, va_list *ap)
{
	char	*octal;
	char	*espaces;
	char	tmp;

	ft_print_octal2(to_print, ap, &octal);
	EXIT_IF_FAIL((octal = handle_octal_precision(to_print, octal)));
	tmp = (to_print->flags->zero && to_print->precision < 0 ? '0' : ' ');
	EXIT_IF_FAIL((espaces = ft_strnew(to_print->taille_mini
	> (int)ft_strlen(octal)
		? to_print->taille_mini - ft_strlen(octal) : 0)));
	to_print->taille_mini > (int)ft_strlen(octal)
		? ft_memset(espaces, tmp, to_print->taille_mini - ft_strlen(octal)) : 0;
	to_print->flags->minus ? ft_putstr(octal) : ft_putstr(espaces);
	to_print->flags->minus ? ft_putstr(espaces) : ft_putstr(octal);
	to_print->size = ft_strlen(octal) + ft_strlen(espaces);
	free(espaces);
	free(octal);
}
