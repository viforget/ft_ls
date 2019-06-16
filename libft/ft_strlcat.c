/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 01:00:58 by viforget          #+#    #+#             */
/*   Updated: 2018/10/25 16:29:03 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst,
		const char *src, size_t size)
{
	size_t i;
	size_t n;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < size)
		i++;
	n = i;
	while (src[i - n] != '\0' && i < size - 1)
	{
		dst[i] = src[i - n];
		i++;
	}
	if (n < size)
		dst[i] = '\0';
	return (n + ft_strlen(src));
}
