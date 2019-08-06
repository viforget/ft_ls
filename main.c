/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/08/06 16:25:41 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void			ft_ls(char *st, char *path)
{
	t_info			*tree;
	DIR				*dir;
	unsigned int	blocks;
	size_t			col[7];

	tree = NULL;
	blocks = 0;
	dir = opendir(path);
	if (dir)
	{
		tree = create_tree(dir, path, &blocks, col);
		closedir(dir);
		if (is_on(g_flags, OPT_L))
		{
			ft_putstr("total ");
			ft_putnbr(blocks);
			ft_putchar('\n');
		}
		aff_tree(tree, col);
		del_tree(tree);
	}
	else if (errno == ENOTDIR)
		ft_putendl(st);
	else
	{
		put_mult_str(3, "ft_ls: ", st, ": No such file or directory\n");
		return ;
	}
}

static void		ft_multi_ls(char **argv, int argc)
{
	int			i;
	size_t		col[7];

	i = 0;
	sort_argv(argv, argc, col);
	while (i < argc)
	{
		ft_ls(argv[i], argv[i]);
		i++;
	}
}

int				main(int argc, char **argv)
{
	int				i;

	g_flags = 0;
	i = parsing(argv);
	if (i == argc)
		ft_ls(".", ".");
	else
		ft_multi_ls(argv + i, argc - i);
	return (0);
}
