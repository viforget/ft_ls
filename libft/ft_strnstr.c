/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 02:15:10 by viforget          #+#    #+#             */
/*   Updated: 2018/10/18 23:46:31 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t ln;

	i = 0;
	ln = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && ln <= len)
	{
		if (ft_memcmp(haystack, needle, ln) == 0 && *haystack == *needle)
		{
			if (i + ln > len)
				return (NULL);
			return ((char *)haystack);
		}
		haystack++;
		i++;
	}
	return (NULL);
}
