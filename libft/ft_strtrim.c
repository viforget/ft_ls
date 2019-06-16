/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 02:05:35 by viforget          #+#    #+#             */
/*   Updated: 2018/10/19 04:24:49 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_trim(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (ft_trim(s[i]) == 1)
	{
		if (*s == '\0')
			return (ft_strnew(0));
		s++;
	}
	while (s[i] != '\0')
		i++;
	while (ft_trim(s[i]) == 1)
		i--;
	if (!(str = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_strncpy(str, s, i + 1);
	str[i + 1] = '\0';
	return (str);
}
