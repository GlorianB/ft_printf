/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 09:28:34 by gbikoumo          #+#    #+#             */
/*   Updated: 2019/10/01 16:02:03 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*handle_fl_plus(t_printf *to_print, char *fl)
{
	if (to_print->flags->plus)
		if (*fl && *fl != '-')
			EXIT_IF_FAIL((fl = ft_strjoin_free("+", fl, 2)));
	if (to_print->flags->space)
		if (*fl && *fl != '-')
			EXIT_IF_FAIL((fl = ft_strjoin_free(" ", fl, 2)));
	return (fl);
}

static char		*handle_fl_width(t_printf *to_print, char *fl)
{
	char	*espace;
	size_t	len;

	len = to_print->taille_mini > (int)ft_strlen(fl)
			? to_print->taille_mini - ft_strlen(fl) : 0;
	EXIT_IF_FAIL((espace = ft_strnew(len)));
	if (to_print->flags->minus)
	{
		if (len)
			espace = ft_memset(espace, ' ', len);
		EXIT_IF_FAIL((fl = ft_strjoin_free(fl, espace, 3)));
	}
	else
	{
		if (len)
			espace = ft_memset(espace, ' ', len);
		EXIT_IF_FAIL((fl = ft_strjoin_free(espace, fl, 3)));
	}
	return (fl);
}

static char		*handle_fl_zero(t_printf *to_print, char *fl)
{
	if (to_print->flags->plus || to_print->flags->space
	|| ft_strchr(fl, '-'))
		while ((int)ft_strlen(fl) < to_print->taille_mini)
			EXIT_IF_FAIL((fl = ft_insertc(&fl, '0', 1)));
	else
		while ((int)ft_strlen(fl) < to_print->taille_mini)
			EXIT_IF_FAIL((fl = ft_strjoin_free("0", fl, 2)));
	return (fl);
}

void			ft_print_fl(t_printf *to_print, va_list *ap)
{
	char	*fl;

	if (to_print->precision < 0)
		to_print->precision = 6;
	if (to_print->flags->l)
		EXIT_IF_FAIL((fl = ft_lftoa(va_arg(*ap, double), to_print->precision)));
	else if (to_print->flags->ld)
		EXIT_IF_FAIL((fl = ft_llftoa_base(va_arg(*ap, long double)
		, 10, to_print->precision)));
	else
		fl = ft_ftoa((float)va_arg(*ap, double), to_print->precision);
	EXIT_IF_FAIL((fl = handle_fl_plus(to_print, fl)));
	if (to_print->flags->zero && to_print->precision < to_print->taille_mini)
		EXIT_IF_FAIL((fl = handle_fl_zero(to_print, fl)));
	else
		EXIT_IF_FAIL((fl = handle_fl_width(to_print, fl)));
	to_print->size += write(1, fl, ft_strlen(fl));
	ft_strdel(&fl);
}
