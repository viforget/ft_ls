/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 19:35:42 by ntom              #+#    #+#             */
/*   Updated: 2019/07/31 22:05:50 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int		ft_option(char *str)
{
	static char		*flag = "lRart";
	size_t			i;
	size_t			j;
	char			error[2];

	j = 1;
	error[1] = '\0';
	while (str[j])
	{
		i = 0;
		while (flag[i])
		{
			if (str[j] == flag[i])
			{
				g_flags |= ON << i;
				break ;
			}
			i++;
			if (flag[i] == '\0')
			{
				error[0] = str[j];
				return (put_mult_str(3, "ft_ls: illegal option -- ",
				error, "\nusage: ft_ls [-Ralrt] [file ...]"));
			}
		}
		j++;
	}
	return (0);
}

int				parsing(char **argv)
{
	size_t			i;

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
			ft_option(argv[i]);
		i++;
	}
	return (i);
}
