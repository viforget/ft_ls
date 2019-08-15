/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 19:35:42 by ntom              #+#    #+#             */
/*   Updated: 2019/08/15 15:19:49 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static int		ft_option(char *str, int j, int i, char *error)
{
	static char		*flag = "lRart";

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
				put_mult_str(3, "ft_ls: illegal option -- ",
				error, "\nusage: ft_ls [-Ralrt] [file ...]\n");
				exit(1);
			}
		}
		j++;
	}
	return (0);
}

static int		init_option(char *str)
{
	size_t			i;
	size_t			j;
	char			error[2];

	j = 1;
	error[1] = '\0';
	i = 0;
	return (ft_option(str, j, i, error));
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
			init_option(argv[i]);
		i++;
	}
	return (i);
}
