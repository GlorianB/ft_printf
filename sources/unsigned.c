/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 07:54:33 by gbikoumo          #+#    #+#             */
/*   Updated: 2019/10/01 15:16:47 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*handle_uns_precision(t_printf *to_print, char *uns)
{
	if (to_print->precision == 0 && *uns == '0')
	{
		ft_strdel(&uns);
		return ((uns = ft_strnew(0)));
	}
	if (to_print->precision > 0)
		while (ft_strlen(uns) < (unsigned)to_print->precision)
			EXIT_IF_FAIL((uns = ft_strjoin_free("0", uns, 2)));
	return (uns);
}

static char		*handle_uns_width(t_printf *to_print, char *uns)
{
	char	*espace;
	size_t	len;

	len = to_print->taille_mini > (int)ft_strlen(uns)
		? to_print->taille_mini - ft_strlen(uns) : 0;
	EXIT_IF_FAIL((espace = ft_strnew(len)));
	if (len)
		espace = ft_memset(espace, ' ', len);
	EXIT_IF_FAIL((uns = to_print->flags->minus
		? ft_strjoin_free(uns, espace, 3) : ft_strjoin_free(espace, uns, 3)));
	return (uns);
}

static char		*handle_uns_zero(t_printf *to_print, char *uns)
{
	while ((int)ft_strlen(uns) < to_print->taille_mini)
		EXIT_IF_FAIL((uns = ft_strjoin_free("0", uns, 2)));
	return (uns);
}

void			ft_print_unsigned(t_printf *to_print, va_list *ap)
{
	char *uns;

	if (to_print->flags->h)
		EXIT_IF_FAIL((uns = ft_utoa_base((unsigned short)
		va_arg(*ap, unsigned), 10)));
	else if (to_print->flags->hh)
		EXIT_IF_FAIL((uns = ft_utoa_base((unsigned char)
		va_arg(*ap, unsigned), 10)));
	else if (to_print->flags->l)
		EXIT_IF_FAIL((uns = ft_ultoa_base(va_arg(*ap, unsigned long), 10)));
	else if (to_print->flags->ll)
		EXIT_IF_FAIL((uns = ft_ulltoa_base(
			va_arg(*ap, unsigned long long), 10)));
	else
		EXIT_IF_FAIL((uns = ft_utoa_base(va_arg(*ap, unsigned), 10)));
	EXIT_IF_FAIL((uns = handle_uns_precision(to_print, uns)));
	if (to_print->flags->zero && to_print->precision < 0)
		EXIT_IF_FAIL((uns = handle_uns_zero(to_print, uns)));
	else
		EXIT_IF_FAIL((uns = handle_uns_width(to_print, uns)));
	ft_putstr(uns);
	to_print->size = ft_strlen(uns);
	free(uns);
}
