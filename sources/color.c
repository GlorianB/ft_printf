/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Antileak <Antileak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 03:08:19 by Antileak          #+#    #+#             */
/*   Updated: 2019/09/22 15:56:12 by lachille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**RED = 31
**GREEN = 32
**YELLOW = 33
**BLUE = 34
**MAGENTA = 35
**CYAN = 36
*/

int		ft_color(char **str, int res)
{
	if (!(ft_strncmp(*str, "{EOC}", 4)))
		ft_putstr("\e[0m");
	else if (!(ft_strncmp(*str, "{RED}", 5)))
		ft_putstr("\e[31m");
	else if (!(ft_strncmp(*str, "{GRE}", 5)))
		ft_putstr("\e[32m");
	else if (!(ft_strncmp(*str, "{YEL}", 5)))
		ft_putstr("\e[33m");
	else if (!(ft_strncmp(*str, "{BLU}", 5)))
		ft_putstr("\e[34m");
	else if (!(ft_strncmp(*str, "{MAG}", 5)))
		ft_putstr("\e[35m");
	else if (!(ft_strncmp(*str, "{CYA}", 5)))
		ft_putstr("\e[36m");
	else
		return (res);
	*str += 5;
	return (res + 5);
}
