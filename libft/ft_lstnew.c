/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbikoumo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:14:37 by gbikoumo          #+#    #+#             */
/*   Updated: 2019/04/15 11:30:29 by gbikoumo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	if ((res = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		if ((res->content = (void *)malloc(content_size)) == NULL)
			return (NULL);
		res->content = ft_memcpy(res->content, content, content_size);
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
