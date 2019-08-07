/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:51:39 by viforget          #+#    #+#             */
/*   Updated: 2019/08/07 16:35:02 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void			aff_error(t_info *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		aff_error(tree->left);
	if (tree->name[0] != '\0')
		put_mult_str(3, "ft_ls: ", tree->name, ": No such file or directory\n");
	if (tree->right != NULL)
		aff_error(tree->right);
}

void			tree_dir(t_info *tree)
{
	static int boo = 0;
	static int boo2 = 0;

	if (tree == NULL)
		return ;
	if (boo2 == 0 && tree->left == NULL && tree->right == NULL)
	{
		ft_ls(tree->name, "./");
		return ;
	}
	else
		boo2 = 1;
	if (tree->left != NULL)
		tree_dir(tree->left);
	if (tree->name[0] != '\0')
	{
		if (boo == 0)
		{
			put_mult_str(2, tree->name, ":\n");
			ft_ls(tree->name, "./");
			boo = 1;
		}
		else
		{
			put_mult_str(3, "\n", tree->name, ":\n");
			ft_ls(tree->name, "./");
		}
	}
	if (tree->right != NULL)
		tree_dir(tree->right);
}

static void		initialize(t_info *tre[3], size_t col[7])
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
}

void			sort_argv(char **argv, int argc, size_t col[7])
{
	int					i;
	DIR					*buf;
	t_info				*tmp;
	t_info				*tre[3];
	unsigned int		blocks;

	i = 0;
	tmp = NULL;
	blocks = 0;
	initialize(tre, col);
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (ft_putendl("ft_ls: fts_open: No such file or directory"));
		tmp = noeud_stock(tmp, argv[i], "./", &blocks);
		if ((buf = opendir(argv[i])))
		{
			tre[0] = bin_stock(tre[0], tmp, FILES);
			closedir(buf);
		}
		else if (errno == ENOTDIR)
		{
			cnt_column(tmp, col);
			tre[1] = bin_stock(tre[1], tmp, FILES);
		}
		else
			tre[2] = bin_stock(tre[2], tmp, ERRORS);
		i++;
	}
	add_column(col);
	aff_error(tre[2]);
	if (tre[1] != NULL)
		aff_tree(tre[1], col);
	tree_dir(tre[0]);
}
