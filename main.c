/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/06/16 21:15:05 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		ft_ls(char **argv, int flags)
{
	struct stat		buf;
	int				i;

	i = 0;
	while (argv[i])
	{
		if (lstat(argv[i], &buf) == -1)
			printf("ft_ls: %s: No such file or directory\n", argv[i]);
		else if (!S_ISDIR(buf.st_mode))
		{
			ft_putendl(argv[i]);
		}
		else (S_ISDIR(buf.st_mode))
			;
		i++;
	}
}

int				main(int argc, char **argv)
{
	int				flags;
	int				i;

	i = parsing(argv, &flags);
	if (i < argc && argv[i][0] == '\0')
		ft_putendl("ft_ls: fts_open: No such file or directory");
	else
		ft_ls(argv + i, flags);
	return (0);
}
