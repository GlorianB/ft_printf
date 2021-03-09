/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 04:22:30 by gbikoumo          #+#    #+#             */
/*   Updated: 2019/10/01 10:39:08 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*handle_hexa_precision(t_printf *to_print, char *hexa)
{
	if (to_print->precision == 0 && *hexa == '0')
	{
		ft_strdel(&hexa);
		return ((hexa = ft_strnew(0)));
	}
	if (to_print->precision > 0)
	{
		while (ft_strlen(hexa) < (unsigned)to_print->precision)
			EXIT_IF_FAIL((hexa = ft_strjoin_free("0", hexa, 2)));
		if (to_print->flags->sharp && !ft_strstr(hexa, "0X"))
			EXIT_IF_FAIL((hexa = ft_strjoin_free("0X", hexa, 2)));
	}
	return (hexa);
}

static void		handle_hexa_width2(t_printf *to_print, char **hexa,
	char *espace, int tmp)
{
	int len;

	len = to_print->taille_mini > tmp
		? to_print->taille_mini - ft_strlen(*hexa) : 0;
	len += (to_print->flags->sharp && ft_strstr(*hexa, "0X") ? 2 : 0);
	EXIT_IF_FAIL((espace = ft_strnew(len)));
	if (to_print->flags->sharp && !ft_strstr(*hexa, "0X"))
		EXIT_IF_FAIL((*hexa = ft_strjoin_free("0X", *hexa, 2)));
	if (len)
		espace = ft_memset(espace, ' ',
			(to_print->flags->sharp ? len - 2 : len));
	EXIT_IF_FAIL((*hexa = ft_strjoin_free(*hexa, espace, 3)));
}

static char		*handle_hexa_width(t_printf *to_print, char *hexa)
{
	char	*espace;
	size_t	len;
	int		tmp;

	espace = NULL;
	tmp = to_print->flags->sharp ? ft_strlen(hexa) + 2 : ft_strlen(hexa);
	if (to_print->flags->minus)
	{
		handle_hexa_width2(to_print, &hexa, espace, tmp);
		return (hexa);
	}
	else
	{
		len = to_print->taille_mini > tmp
			? to_print->taille_mini - ft_strlen(hexa) : 0;
		len += (to_print->flags->sharp && ft_strstr(hexa, "0X") ? 2 : 0);
		EXIT_IF_FAIL((espace = ft_strnew(len)));
		if (len)
			espace = ft_memset(espace, ' ',
				(to_print->flags->sharp ? len - 2 : len));
		if (to_print->flags->sharp && !ft_strstr(hexa, "0X"))
			EXIT_IF_FAIL((hexa = ft_strjoin_free("0X", hexa, 2)));
		EXIT_IF_FAIL((hexa = ft_strjoin_free(espace, hexa, 3)));
		return (hexa);
	}
}

static char		*handle_hexa_zero(t_printf *to_print, char *hexa)
{
	while ((int)ft_strlen(hexa) < (to_print->flags->sharp
		? to_print->taille_mini - 2 : to_print->taille_mini))
		EXIT_IF_FAIL((hexa = ft_strjoin_free("0", hexa, 2)));
	if (to_print->flags->sharp && !ft_strstr(hexa, "0X"))
		EXIT_IF_FAIL((hexa = ft_strjoin_free("0X", hexa, 2)));
	return (hexa);
}

void			ft_print_hexa(t_printf *to_print, va_list *ap)
{
	char	*hexa;

	if (to_print->flags->h)
		EXIT_IF_FAIL((hexa = ft_utoa_base(
			(unsigned short)va_arg(*ap, unsigned), 16)));
	else if (to_print->flags->hh)
		EXIT_IF_FAIL((hexa = ft_utoa_base(
			(unsigned char)va_arg(*ap, unsigned), 16)));
	else if (to_print->flags->l)
		EXIT_IF_FAIL((hexa = ft_ultoa_base(va_arg(*ap, unsigned long), 16)));
	else if (to_print->flags->ll)
		EXIT_IF_FAIL((hexa = ft_ulltoa_base(
			va_arg(*ap, unsigned long long), 16)));
	else
		EXIT_IF_FAIL((hexa = ft_utoa_base(va_arg(*ap, unsigned), 16)));
	*hexa == '0' ? to_print->flags->sharp = 0 : 0;
	EXIT_IF_FAIL((hexa = handle_hexa_precision(to_print, hexa)));
	if (to_print->flags->zero && to_print->precision < 0)
		EXIT_IF_FAIL((hexa = handle_hexa_zero(to_print, hexa)));
	else
		EXIT_IF_FAIL((hexa = handle_hexa_width(to_print, hexa)));
	to_print->conversion == 'x' ? ft_str_minimize(&hexa) : 0;
	ft_putstr(hexa);
	to_print->size = ft_strlen(hexa);
	free(hexa);
}
