/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/08/17 12:13:21 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int				ft_find_right(t_info *tree)
{
	if (is_on(g_flags, OPT_A))
		return (1);
	while(tree)
	{
		if (tree->name[0] != '.')
			return (1);
		tree = tree->right;
	}
	return (0);
}

void			ft_ls(char *path)
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
		if (is_on(g_flags, OPT_L) && ft_find_right(tree))
		{
			ft_putstr("total ");
			ft_putnbr(blocks);
			ft_putchar('\n');
		}
		aff_tree(tree, col);
		del_tree(tree);
	}
}

static void		ft_multi_ls(char **argv, int argc)
{
	int			i;
	size_t		col[7];

	i = 0;
	sort_argv(argv, argc, col);
}

int				main(int argc, char **argv)
{
	int				i;

	g_flags = 0;
	i = parsing(argv);
	if (i == argc)
		ft_ls(".");
	else
		ft_multi_ls(argv + i, argc - i);
	return (0);
}
