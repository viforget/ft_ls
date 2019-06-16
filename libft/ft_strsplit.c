/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 19:54:28 by viforget          #+#    #+#             */
/*   Updated: 2018/10/25 16:31:53 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_freedom(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static	int		ft_tcl(const char *s, char c)
{
	int		ct;
	int		page;

	page = 0;
	ct = 0;
	while (*s != '\0')
	{
		if (page == 1 && *s == c)
			page = 0;
		if (page == 0 && *s != c)
		{
			page = 1;
			ct++;
		}
		s++;
	}
	return (ct);
}

static	int		ft_wlen(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**t;
	int		nb_word;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nb_word = ft_tcl((const char *)s, c);
	if (!(t = (char **)malloc(sizeof(*t) * (ft_tcl((const char *)s, c) + 1))))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		t[i] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
		if (t[i] == NULL)
		{
			ft_freedom(t, i);
			return (NULL);
		}
		s = s + ft_wlen(s, c);
		i++;
	}
	t[i] = NULL;
	return (t);
}
