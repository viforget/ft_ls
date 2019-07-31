/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_del_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:24:49 by ntom              #+#    #+#             */
/*   Updated: 2019/07/31 18:57:51 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#define _6MONTHS 15552000

void		del_tree(t_info *tree)
{
	if (tree->left != NULL)
		del_tree(tree->left);
	if (is_on(g_flags, OPT_UR) && tree->type == 4
			&& ft_strcmp(tree->name, ".") != 0
			&& ft_strcmp(tree->name, "..") != 0
			&& (is_on(g_flags, OPT_A) || tree->name[0] != '.'))
	{
		put_mult_str(4, "\n", tree->path, ":", "\n");
		put_mult_str(3, tree->name, tree->path, "\n");
		ft_ls(tree->name, tree->path);
	}
	if (tree->right != NULL)
		del_tree(tree->right);
	ft_strdel(&tree->name);
	ft_strdel(&tree->path);
	ft_strdel(&tree->ftr);
	free(tree);
}

static void		aff_l(t_info *tree)
{
	if (tree->size != NULL)
		put_mult_str(14,
			tree->ftr, " ",
			tree->links, " ",
			tree->uid, " ",
			tree->grid, " ",
			tree->size, " ",
			tree->month_day, " ",
			tree->hour_year, " ");
	else
		put_mult_str(16,
			tree->ftr, " ",
			tree->links, " ",
			tree->uid, " ",
			tree->grid, " ",
			tree->min, ", ",
			tree->maj, " ",
			tree->month_day, " ",
			tree->hour_year, " ");
}

void		aff_tree(t_info *tree)
{
	if (tree->left != NULL)
		aff_tree(tree->left);
	if (is_on(g_flags, OPT_A) || tree->name[0] != '.')
	{
		if (is_on(g_flags, OPT_L))
			aff_l(tree);
		ft_putendl(tree->name);
	}
	if (tree->right != NULL)
		aff_tree(tree->right);
}
