/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:53:50 by viforget          #+#    #+#             */
/*   Updated: 2018/10/18 23:56:57 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const	unsigned	char	*srcc;
	unsigned			char	*dstc;

	srcc = src;
	dstc = dst;
	if (dstc > srcc)
	{
		while (len > 0)
		{
			dstc[len - 1] = srcc[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dstc, srcc, len);
	return (dst);
}
