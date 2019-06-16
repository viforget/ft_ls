/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 02:37:09 by viforget          #+#    #+#             */
/*   Updated: 2018/10/18 23:13:08 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	int ln;

	ln = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		if (ft_strncmp((char *)haystack, (char *)needle, ln) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
