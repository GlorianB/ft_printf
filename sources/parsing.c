/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:24:30 by santa             #+#    #+#             */
/*   Updated: 2019/10/01 02:03:54 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_printf		*parse_flags(const char **format, t_printf *to_print)
{
	while (**format && ft_strchr("#0-+ ", **format))
	{
		if (**format == '#')
			to_print->flags->sharp = 1;
		else if (**format == '0' && !(to_print->flags->minus))
			to_print->flags->zero = 1;
		else if (**format == ' ' && !(to_print->flags->plus))
			to_print->flags->space = 1;
		else if (**format == '-')
		{
			to_print->flags->minus = 1;
			to_print->flags->zero = 0;
		}
		else if (**format == '+')
		{
			to_print->flags->plus = 1;
			to_print->flags->space = 0;
		}
		(*format)++;
	}
	return (to_print);
}

static t_printf		*parse_taille_mini(const char **format,
	t_printf *to_print, va_list *ap)
{
	int tmp;

	if (ft_isdigit(**format))
	{
		to_print->taille_mini = ft_atoi(*format);
		*format += ft_size_nb(to_print->taille_mini);
	}
	else if (**format == '*')
	{
		tmp = va_arg(*ap, int);
		if (tmp < 0)
		{
			tmp = (tmp == -2147483648 ? 2147483647 : -tmp);
			to_print->flags->minus = 1;
			to_print->flags->zero = 0;
		}
		to_print->taille_mini = tmp;
		(*format)++;
		if (ft_isdigit(**format))
		{
			to_print->taille_mini = ft_atoi(*format);
			*format += ft_size_nb(to_print->taille_mini);
		}
	}
	return (to_print);
}

static t_printf		*parse_precision(const char **format,
	t_printf *to_print, va_list *ap)
{
	if (**format != '.')
		return (to_print);
	(*format)++;
	if (ft_isdigit(**format))
	{
		if (**format == '0')
			while (*format && **format == '0')
				(*format)++;
		to_print->precision = ft_isdigit(**format) ? ft_atoi(*format) : 0;
		*format += ft_isdigit(**format) ? ft_size_nb(to_print->precision) : 0;
	}
	else if (**format == '*')
	{
		to_print->precision = va_arg(*ap, int);
		to_print->precision < 0 ? to_print->precision = -1 : 0;
		(*format)++;
		if (ft_isdigit(**format))
		{
			to_print->taille_mini = ft_atoi(*format);
			*format += ft_size_nb(to_print->taille_mini);
		}
	}
	else
		to_print->precision = 0;
	return (to_print);
}

static t_printf		*parse_modifiers(const char **format, t_printf *to_print)
{
	if (**format == 'h' && (*(*format + 1)) == 'h')
		to_print->flags->hh = 1;
	else if ((**format == 'l' && (*(*format + 1)) == 'l') || **format == 'z')
		to_print->flags->ll = 1;
	else if (**format == 'L' && (*(*format + 1) == 'f'))
		to_print->flags->ld = 1;
	else if (**format == 'h')
		to_print->flags->h = 1;
	else if (**format == 'l')
		to_print->flags->l = 1;
	to_print->flags->l || to_print->flags->h
		|| to_print->flags->ld ? (*format)++ : 0;
	to_print->flags->ll || to_print->flags->hh ? (*format) += 2 : 0;
	return (to_print);
}

t_printf			*parse_printf(const char **format,
	t_printf *to_print, va_list *ap)
{
	to_print = parse_flags(format, to_print);
	**format ? to_print = parse_taille_mini(format, to_print, ap) : 0;
	**format ? to_print = parse_precision(format, to_print, ap) : 0;
	**format ? to_print = parse_modifiers(format, to_print) : 0;
	**format ? to_print->conversion = *(*(format))++ : 0;
	return (to_print);
}
