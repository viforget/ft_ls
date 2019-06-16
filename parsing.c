/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 19:35:42 by ntom              #+#    #+#             */
/*   Updated: 2019/06/16 20:53:40 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int	ft_option(char *str, int *flags)
{
	static char		*flag = "lRart";
	int				i;
	int				j;

	j = 1;
	while (str[j])
	{
		i = 0;
		while (flag[i])
		{
			if (str[j] == flag[i])
			{
				*flags |= ON << i;
				break ;
			}
			i++;
			if (flag[i] == '\0')
				return (printf("ft_ls: illegal option -- %c\n"
				"usage: ft_ls [-Ralrt] [file ...]\n", str[j]));
		}
		j++;
	}
	return (0);
}

int				parsing(char **argv, int *flags)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if ((argv[i][0] == '-' && argv[i][1] == '\0') || argv[i][0] != '-')
			break ;
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
		{
			i++;
			break ;
		}
		if (argv[i][0] == '-')
			ft_option(argv[i], flags);
		i++;
	}
	return (i);
}
