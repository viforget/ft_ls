/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:51:39 by viforget          #+#    #+#             */
/*   Updated: 2019/08/16 00:44:00 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void			tree_dir2(t_info *tree)
{
	static int boo = 0;

	if (boo == 0)
	{
		put_mult_str(2, tree->name, ":\n");
		ft_ls(tree->name);
		boo = 1;
	}
	else
	{
		put_mult_str(3, "\n", tree->name, ":\n");
		ft_ls(tree->name);
	}
}

void				tree_dir(t_info *tree, int argc)
{
	static int boo = 0;

	if (tree == NULL)
		return ;
	if (argc == 1)
	{
		ft_ls(tree->name);
		return ;
	}
	else
		boo = 1;
	if (tree->left != NULL)
		tree_dir(tree->left, argc);
	if (tree->name[0] != '\0')
		tree_dir2(tree);
	if (tree->right != NULL)
		tree_dir(tree->right, argc);
}

static void			initialize(t_info *tre[3], size_t col[7],
	unsigned int *blocks, int *i)
{
	tre[0] = NULL;
	tre[1] = NULL;
	tre[2] = NULL;
	col[0] = 11;
	col[1] = 0;
	col[2] = 0;
	col[3] = 0;
	col[4] = 0;
	col[5] = 0;
	col[6] = 0;
	*i = 0;
	*blocks = 0;
}

static unsigned int	sort_argv2(char *argv, t_info *tmp, t_info *tre[3],
	size_t *col[7])
{
	unsigned int		blocks;
	DIR					*buf;

	blocks = 0;
	if (argv[0] == '\0')
	{
		ft_putendl("ft_ls: fts_open: No such file or directory");
		return (0);
	}
	tmp = noeud_stock(tmp, argv, "", &blocks);
	if ((buf = opendir(argv)))
	{
		tre[0] = bin_stock(tre[0], tmp, FILES);
		closedir(buf);
	}
	else if (errno == ENOTDIR)
	{
		cnt_column(tmp, *col);
		tre[1] = bin_stock(tre[1], tmp, FILES);
	}
	else
		tre[2] = bin_stock(tre[2], tmp, ERRORS);
	return (blocks);
}

void				sort_argv(char **argv, int argc, size_t col[7])
{
	int					i;
	t_info				*tmp;
	t_info				*tre[3];
	unsigned int		blocks;

	tmp = NULL;
	initialize(tre, col, &blocks, &i);
	while (i < argc)
	{
		sort_argv2(argv[i], tmp, tre, &col);
		i++;
	}
	add_column(col);
	aff_error(tre[2]);
	if (tre[1] != NULL)
	{
		if (is_off(g_flags, OPT_A))
		{
			g_flags |= ON << OPT_A;
			aff_tree(tre[1], col);
			g_flags &= ~(ON << OPT_A);
		}
		else
			aff_tree(tre[1], col);
		if (tre[0] != NULL)
			ft_putchar('\n');
	}
	tree_dir(tre[0], argc);
	del_tree(tre[0]);
	del_tree(tre[1]);
	del_tree(tre[2]);
}
