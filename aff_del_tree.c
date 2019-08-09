/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_del_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:24:49 by ntom              #+#    #+#             */
/*   Updated: 2019/08/07 18:02:13 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#define _6MONTHS 15552000

void			del_tree(t_info *tree)
{
	if (tree->left != NULL)
		del_tree(tree->left);
	if (is_on(g_flags, OPT_UR) && tree->stats.st_mode >= DIRECTOR
			&& tree->stats.st_mode < BLOCKSPE
			&& ft_strcmp(tree->name, ".") != 0
			&& ft_strcmp(tree->name, "..") != 0
			&& (is_on(g_flags, OPT_A) || tree->name[0] != '.'))
	{
		put_mult_str(4, "\n", tree->path, ":", "\n");
		ft_ls(tree->path);
	}
	if (tree->right != NULL)
		del_tree(tree->right);
	ft_strdel(&tree->path);
	ft_strdel(&tree->name);
	ft_strdel(&tree->ftr);
	ft_strdel(&tree->links);
	ft_strdel(&tree->uid);
	ft_strdel(&tree->grid);
	ft_strdel(&tree->size_majmin);
	ft_strdel(&tree->month_day);
	ft_strdel(&tree->hour_year);
	free(tree);
}

static void		aff_l(t_info *tree, size_t col[7])
{
	char	*str;

	str = string_l(col, tree);
	ft_putstr(str);
	ft_strdel(&str);
}

void			aff_tree(t_info *tree, size_t col[7])
{
	if (tree->left != NULL)
		aff_tree(tree->left, col);
	if (is_on(g_flags, OPT_A) || tree->name[0] != '.')
	{
		if (is_on(g_flags, OPT_L))
			aff_l(tree, col);
		ft_putendl(tree->name);
	}
	if (tree->right != NULL)
		aff_tree(tree->right, col);
}
