/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/06/16 19:29:25 by ntom             ###   ########.fr       */
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
				return (printf("ft_ls: illegal option -- %c\n", str[j]));
		}
		j++;
	}
	return (0);
}

static int	parsing(char **argv, int *flags)
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

int			main(int argc, char **argv)
{
	int		i;
	int		flags;

	i = parsing(argv, &flags);
	return (0);
}
