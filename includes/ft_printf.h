/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 13:31:46 by santa             #+#    #+#             */
/*   Updated: 2019/10/04 15:05:55 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define EXIT_IF_FAIL(x) ((x == NULL ? exit(1) : 0))
# include "../libft/libft.h"
# include <stdarg.h>

typedef	struct	s_flags
{
	short	sharp;
	short	zero;
	short	minus;
	short	plus;
	short	space;
	short	h;
	short	hh;
	short	l;
	short	ll;
	short	ld;
}				t_flags;

typedef	struct	s_printf
{
	t_flags	*flags;
	int		taille_mini;
	int		precision;
	int		size;
	char	conversion;
}				t_printf;

int				ft_printf(const char *format, ...);
t_printf		*parse_printf(const char **format,
				t_printf *to_print, va_list *ap);
void			ft_print_chr(t_printf *to_print, va_list *ap);
void			ft_print_str(t_printf *to_print, va_list *ap);
void			ft_print_ptr(t_printf *to_print, va_list *ap);
void			ft_print_octal(t_printf *to_print, va_list *ap);
void			ft_print_hexa(t_printf *to_print, va_list *ap);
void			ft_print_unsigned(t_printf *to_print, va_list *ap);
void			ft_print_integer(t_printf *to_print, va_list *ap);
void			ft_print_fl(t_printf *to_print, va_list *ap);
void			ft_print_bin(t_printf *to_print, va_list *ap);
int				ft_color(char **str, int res);

#endif
