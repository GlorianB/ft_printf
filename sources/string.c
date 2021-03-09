/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:01:54 by santa             #+#    #+#             */
/*   Updated: 2019/10/01 15:15:50 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_print_chr(t_printf *to_print, va_list *ap)
{
	char	c;
	char	*espaces;
	char	tmp;

	if (to_print->conversion == '%')
		c = '%';
	else
		c = va_arg(*ap, int);
	EXIT_IF_FAIL((espaces = ft_strnew(to_print->taille_mini > 0
		? to_print->taille_mini - 1 : 0)));
	tmp = to_print->flags->zero ? '0' : ' ';
	to_print->taille_mini
		? ft_memset(espaces, tmp, to_print->taille_mini - 1) : 0;
	to_print->flags->minus ? ft_putchar(c) : ft_putstr(espaces);
	to_print->flags->minus ? ft_putstr(espaces) : ft_putchar(c);
	to_print->size = ft_strlen(espaces) + 1;
	free(espaces);
}

void			ft_print_str(t_printf *to_print, va_list *ap)
{
	char *str;
	char *espaces;
	char tmp;

	if (to_print->precision < 0)
	{
		if (!(str = ft_strdup(va_arg(*ap, char*))))
			EXIT_IF_FAIL((str = ft_strdup("(null)")));
	}
	else if (!(str = ft_strsub(va_arg(*ap, char*), 0, to_print->precision)))
	{
		ft_strdel(&str);
		EXIT_IF_FAIL((str = ft_strsub("(null)", 0, to_print->precision)));
	}
	EXIT_IF_FAIL((espaces = ft_strnew(to_print->taille_mini
	> (int)ft_strlen(str)
		? to_print->taille_mini - ft_strlen(str) : 0)));
	tmp = to_print->flags->zero ? '0' : ' ';
	to_print->taille_mini > (int)ft_strlen(str)
		? ft_memset(espaces, tmp, to_print->taille_mini - ft_strlen(str)) : 0;
	to_print->flags->minus ? ft_putstr(str) : ft_putstr(espaces);
	to_print->flags->minus ? ft_putstr(espaces) : ft_putstr(str);
	to_print->size = ft_strlen(str) + ft_strlen(espaces);
	free(str);
	free(espaces);
}

static void		handle_ptr_precision(t_printf *to_print, char **res)
{
	if (to_print->flags->zero && to_print->precision < 0)
		while ((int)ft_strlen(*res) < to_print->taille_mini)
			EXIT_IF_FAIL((*res = ft_insertc(res, '0', 2)));
	else
		while (to_print->precision > -1 && (ft_strlen(*res) < 1 ? 0
		: (int)ft_strlen(*res) - 2) < to_print->precision)
			EXIT_IF_FAIL((*res = ft_insertc(res, '0', 2)));
}

void			ft_print_ptr(t_printf *to_print, va_list *ap)
{
	unsigned long	adresse;
	char			*res;
	char			*espaces;

	adresse = (unsigned long)va_arg(*ap, void *);
	if (adresse == 0 && to_print->precision == 0)
		EXIT_IF_FAIL((res = ft_strdup("0x")));
	else
		EXIT_IF_FAIL((res = ft_strjoin_free("0x",
		ft_ultoa_base(adresse, 16), 2)));
	ft_str_minimize(&res);
	handle_ptr_precision(to_print, &res);
	EXIT_IF_FAIL((espaces = ft_strnew(to_print->taille_mini
	> (int)ft_strlen(res)
		? to_print->taille_mini - ft_strlen(res) : 0)));
	to_print->taille_mini > (int)ft_strlen(res)
		? ft_memset(espaces, ' ', to_print->taille_mini - ft_strlen(res)) : 0;
	to_print->flags->minus ? ft_putstr(res) : ft_putstr(espaces);
	to_print->flags->minus ? ft_putstr(espaces) : ft_putstr(res);
	to_print->size = ft_strlen(res) + ft_strlen(espaces);
	free(espaces);
	free(res);
}
