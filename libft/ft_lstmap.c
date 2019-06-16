/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 23:14:16 by viforget          #+#    #+#             */
/*   Updated: 2018/10/19 23:44:06 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*maillon_un;
	t_list	*liste;

	if (!lst || !f)
		return (NULL);
	maillon_un = f(lst);
	liste = maillon_un;
	while (lst->next)
	{
		lst = lst->next;
		if (!(liste->next = f(lst)))
		{
			return (NULL);
		}
		liste = liste->next;
	}
	return (maillon_un);
}
