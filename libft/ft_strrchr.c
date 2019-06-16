/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 01:54:53 by viforget          #+#    #+#             */
/*   Updated: 2018/10/16 02:26:20 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;
	int		i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	t = 0;
	while (i != 0)
	{
		i--;
		s--;
		if (*s == (char)c)
		{
			t = (char *)s;
			return (t);
		}
	}
	return (NULL);
}
