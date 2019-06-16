/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:29:14 by viforget          #+#    #+#             */
/*   Updated: 2018/10/16 06:43:30 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*st;

	i = 0;
	if (len == 0)
		return (b);
	st = (unsigned char *)b;
	while (i < len)
	{
		st[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
