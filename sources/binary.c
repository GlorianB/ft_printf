/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 04:53:19 by lachille          #+#    #+#             */
/*   Updated: 2019/10/02 23:43:35 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*handle_bin_precision(t_printf *to_print, char *bin)
{
	if (to_print->precision == 0 && *bin == '0')
	{
		ft_strdel(&bin);
		return ((bin = ft_strnew(0)));
	}
	if (to_print->precision > 0)
	{
		if (to_print->flags->plus || to_print->flags->space
			|| ft_strchr(bin, '-'))
			while ((int)ft_strlen(bin) <= (to_print->precision < 0
					? to_print->precision * -1 : to_print->precision))
				EXIT_IF_FAIL((bin = ft_insertc(&bin, '0', 1)));
		else
			while ((int)ft_strlen(bin) < (to_print->precision < 0
					? to_print->precision * -1 : to_print->precision))
				EXIT_IF_FAIL((bin = ft_insertc(&bin, '0', 0)));
	}
	return (bin);
}

static char		*handle_bin_width(t_printf *to_print, char *bin)
{
	char	*espace;
	size_t	len;

	len = to_print->taille_mini > (int)ft_strlen(bin)
			? to_print->taille_mini - ft_strlen(bin) : 0;
	EXIT_IF_FAIL((espace = ft_strnew(len)));
	if (to_print->flags->minus)
	{
		if (len)
			espace = ft_memset(espace, ' ', len);
		EXIT_IF_FAIL((bin = ft_strjoin_free(bin, espace, 1)));
	}
	else
	{
		if (len)
			espace = ft_memset(espace, ' ', len);
		EXIT_IF_FAIL((bin = ft_strjoin_free(espace, bin, 2)));
	}
	free(espace);
	return (bin);
}

static char		*handle_bin_zero(t_printf *to_print, char *bin)
{
	if (to_print->flags->plus || to_print->flags->space
	|| ft_strchr(bin, '-'))
		while ((int)ft_strlen(bin) < to_print->taille_mini)
			EXIT_IF_FAIL((bin = ft_insertc(&bin, '0', 1)));
	else
		while ((int)ft_strlen(bin) < to_print->taille_mini)
			EXIT_IF_FAIL((bin = ft_strjoin_free("0", bin, 2)));
	return (bin);
}

void			ft_print_bin(t_printf *to_print, va_list *ap)
{
	char *bin;

	EXIT_IF_FAIL((bin = ft_illtoa_base(va_arg(*ap, long long), 2)));
	EXIT_IF_FAIL((bin = handle_bin_precision(to_print, bin)));
	if (to_print->flags->zero && to_print->precision < 0)
		EXIT_IF_FAIL((bin = handle_bin_zero(to_print, bin)));
	else
		EXIT_IF_FAIL((bin = handle_bin_width(to_print, bin)));
	ft_putstr(bin);
	to_print->size = ft_strlen(bin);
	free(bin);
}
