/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 00:36:07 by viforget          #+#    #+#             */
/*   Updated: 2018/10/21 17:59:43 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	if (!(lst = (t_list *)malloc(sizeof(t_list) * (content_size))))
		return (NULL);
	if (!content)
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	else
	{
		if (!(lst->content = (void *)malloc(content_size)))
		{
			free(lst);
			return (NULL);
		}
		lst->content_size = content_size;
		ft_memcpy(lst->content, content, content_size);
	}
	lst->next = NULL;
	return (lst);
}
