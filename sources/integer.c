/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 05:02:29 by gbikoumo          #+#    #+#             */
/*   Updated: 2019/10/01 13:58:43 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*handle_integer_plus(t_printf *to_print, char *integer)
{
	if (to_print->flags->plus && *integer == '0' && !to_print->precision)
	{
		free(integer);
		EXIT_IF_FAIL((integer = ft_strdup("+")));
		return (integer);
	}
	if (to_print->flags->plus)
		if (*integer && *integer != '-')
			EXIT_IF_FAIL((integer = ft_strjoin_free("+", integer, 2)));
	if (to_print->flags->space)
		if (*integer && *integer != '-')
		{
			if (*integer != '0' || (*integer == '0' && to_print->precision < 0))
				EXIT_IF_FAIL((integer = ft_strjoin_free(" ", integer, 2)));
			else
			{
				free(integer);
				EXIT_IF_FAIL((integer = ft_strjoin_free(" ", "", 0)));
			}
		}
	return (integer);
}

static char		*handle_integer_precision(t_printf *to_print, char *integer)
{
	if (to_print->precision == 0 && *integer == '0')
	{
		free(integer);
		return ((integer = ft_strnew(0)));
	}
	if (to_print->precision > 0)
	{
		if (to_print->flags->plus || to_print->flags->space
			|| ft_strchr(integer, '-'))
			while ((int)ft_strlen(integer) <= (to_print->precision < 0
					? to_print->precision * -1 : to_print->precision))
				EXIT_IF_FAIL((integer = ft_insertc(&integer, '0', 1)));
		else
			while ((int)ft_strlen(integer) < (to_print->precision < 0
					? to_print->precision * -1 : to_print->precision))
				EXIT_IF_FAIL((integer = ft_insertc(&integer, '0', 0)));
	}
	return (integer);
}

static char		*handle_integer_width(t_printf *to_print, char *integer)
{
	char	*espace;
	size_t	len;

	len = to_print->taille_mini > (int)ft_strlen(integer)
			? to_print->taille_mini - ft_strlen(integer) : 0;
	EXIT_IF_FAIL((espace = ft_strnew(len)));
	if (to_print->flags->minus)
	{
		if (len)
			espace = ft_memset(espace, ' ', len);
		EXIT_IF_FAIL((integer = ft_strjoin_free(integer, espace, 1)));
	}
	else
	{
		if (len)
			espace = ft_memset(espace, ' ', len);
		EXIT_IF_FAIL((integer = ft_strjoin_free(espace, integer, 2)));
	}
	free(espace);
	return (integer);
}

static char		*handle_integer_zero(t_printf *to_print, char *integer)
{
	if (to_print->flags->plus || to_print->flags->space
	|| ft_strchr(integer, '-'))
		while ((int)ft_strlen(integer) < to_print->taille_mini)
			EXIT_IF_FAIL((integer = ft_insertc(&integer, '0', 1)));
	else
		while ((int)ft_strlen(integer) < to_print->taille_mini)
			EXIT_IF_FAIL((integer = ft_strjoin_free("0", integer, 2)));
	return (integer);
}

void			ft_print_integer(t_printf *to_print, va_list *ap)
{
	char *integer;

	if (to_print->flags->h)
		EXIT_IF_FAIL((integer = ft_itoa_base((short)va_arg(*ap, int), 10)));
	else if (to_print->flags->hh)
		EXIT_IF_FAIL((integer = ft_itoa_base((char)va_arg(*ap, int), 10)));
	else if (to_print->flags->l)
		EXIT_IF_FAIL((integer = ft_iltoa_base(va_arg(*ap, long), 10)));
	else if (to_print->flags->ll)
		EXIT_IF_FAIL((integer = ft_illtoa_base(va_arg(*ap, long long), 10)));
	else
		EXIT_IF_FAIL((integer = ft_itoa_base(va_arg(*ap, int), 10)));
	EXIT_IF_FAIL((integer = handle_integer_plus(to_print, integer)));
	EXIT_IF_FAIL((integer = handle_integer_precision(to_print, integer)));
	if (to_print->flags->zero && to_print->precision < 0)
		EXIT_IF_FAIL((integer = handle_integer_zero(to_print, integer)));
	else
		EXIT_IF_FAIL((integer = handle_integer_width(to_print, integer)));
	ft_putstr(integer);
	to_print->size = ft_strlen(integer);
	free(integer);
}
