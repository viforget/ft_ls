/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:51:39 by viforget          #+#    #+#             */
/*   Updated: 2019/08/17 15:26:23 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

static void			tree_dir2(t_info *directories)
{
	static int boo = 0;

	if (boo == 0)
	{
		put_mult_str(2, directories->name, ":\n");
		ft_ls(directories->name);
		boo = 1;
	}
	else
	{
		put_mult_str(3, "\n", directories->name, ":\n");
		ft_ls(directories->name);
	}
}

void				tree_dir(t_info *directories, int argc)
{
	static int boo = 0;

	if (directories == NULL)
		return ;
	if (argc == 1)
	{
		ft_ls(directories->name);
		return ;
	}
	else
		boo = 1;
	if (directories->left != NULL)
		tree_dir(directories->left, argc);
	if (directories->name[0] != '\0')
		tree_dir2(directories);
	if (directories->right != NULL)
		tree_dir(directories->right, argc);
}

static void			initialize(t_info *tree[3], size_t col[7],
	unsigned int *blocks, int *i)
{
	tree[TREE_DIRECTORIES] = NULL;
	tree[TREE_FILES] = NULL;
	tree[TREE_ERRORS] = NULL;
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

static unsigned int	sort_argv2(char *argv, t_info *tmp, t_info *tree[3],
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
		tree[TREE_DIRECTORIES] = bin_stock(tree[TREE_DIRECTORIES], tmp, FILES);
		closedir(buf);
	}
	else if (errno == ENOTDIR)
	{
		cnt_column(tmp, *col);
		tree[TREE_FILES] = bin_stock(tree[TREE_FILES], tmp, FILES);
	}
	else
		tree[TREE_ERRORS] = bin_stock(tree[TREE_ERRORS], tmp, ERRORS);
	return (blocks);
}

void				sort_argv(char **argv, int argc, size_t col[7])
{
	int					i;
	t_info				*tmp;
	t_info				*tree[3];
	unsigned int		blocks;

	tmp = NULL;
	initialize(tree, col, &blocks, &i);
	while (i < argc)
		sort_argv2(argv[i++], tmp, tree, &col);
	add_column(col);
	aff_error(tree[TREE_ERRORS]);
	if (tree[TREE_FILES] != NULL)
		aff_args(col, tree[TREE_FILES], tree[TREE_DIRECTORIES]);
	tree_dir(tree[TREE_DIRECTORIES], argc);
	del_tree(tree[TREE_ERRORS]);
	del_tree(tree[TREE_FILES]);
	del_tree(tree[TREE_DIRECTORIES]);
}
