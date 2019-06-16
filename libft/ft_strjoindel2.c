/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoindel2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 10:34:05 by viforget          #+#    #+#             */
/*   Updated: 2019/04/13 10:35:06 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoindel2(char *s1, char *s2)
{
	int		i;
	int		i2;
	char	*str;
	int		len;

	i = 0;
	i2 = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i2] = s1[i];
		i++;
		i2++;
	}
	i = 0;
	while (s2[i] != '\0')
		str[i2++] = s2[i++];
	str[i2] = '\0';
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (str);
}
