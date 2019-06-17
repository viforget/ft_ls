/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/06/18 01:25:21 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void		init_tree(struct stat *buf, char *argv, t_info *i, char *path)
{
	i->name = ft_strdup(argv);
	i->path = ft_strdup(path);
	i->status = lstat(argv, buf);
	i->stats = *buf;
	i->left = NULL;
	i->right = NULL;
}

static void		ft_ls(char **argv, int flags, int argc)
{
	struct stat		buf;
	size_t			i;
	t_info			infos;
	t_info			origin;

	i = 1;
	init_tree(&buf, argv[0], &infos, "./");
	origin = infos;
	while (i < argc)
	{
		if (i < argc && argv[i][0] == '\0')
			return (ft_putendl("ft_ls: fts_open: No such file or directory"));
		lstat(argv[i], &buf);

		i++;
	}
}

int				main(int argc, char **argv)
{
	int				flags;
	size_t			i;

	i = parsing(argv, &flags);
	ft_ls(argv + i, flags, argc - i);
	return (0);
}
