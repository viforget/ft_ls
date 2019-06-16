/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 23:01:17 by viforget          #+#    #+#             */
/*   Updated: 2018/12/06 19:09:56 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strcut(char (*str)[BUFF_SIZE], int n)
{
	int i;

	if (n == 0)
		return (*str);
	i = 0;
	while ((*str)[n + i])
	{
		(*str)[i] = (*str)[i + n];
		i++;
	}
	(*str)[i] = '\0';
	return (*str);
}

static	int		strlenb(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int				get_next_line(const int fd, char **line)
{
	static	char	buf[BUFF_SIZE];
	int				rd;
	char			*lin;

	if (!(lin = ft_strnew(0)) || fd < 0 || !line)
		return (-1);
	rd = BUFF_SIZE;
	ft_strcut(&buf, strlenb(buf) + 1);
	lin = ft_strnjoindel(lin, buf, strlenb(buf));
	while (strlenb(buf) == (int)ft_strlen(buf) && rd == BUFF_SIZE)
	{
		ft_bzero(buf, BUFF_SIZE);
		rd = read(fd, buf, BUFF_SIZE);
		if (rd > 0)
			lin = ft_strnjoindel(lin, buf, strlenb(buf));
	}
	*line = lin;
	if (rd < 0)
		return (-1);
	if (rd == 0 && **line == '\0')
		return (0);
	return (1);
}
