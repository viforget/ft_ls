/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_del_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:24:49 by ntom              #+#    #+#             */
/*   Updated: 2019/07/10 14:54:47 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

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
	ft_putstr(tree->ftr);
	if (tree->stats.st_nlink < 10)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr(tree->stats.st_nlink);
	ft_putchar(' ');
	if (getpwuid(tree->stats.st_uid) == NULL)
	{
		ft_putnbr(tree->stats.st_uid);
		ft_putchar(' ');
	}
	else
		put_mult_str(2, getpwuid(tree->stats.st_uid)->pw_name, "  ");
	if (getgrgid(tree->stats.st_gid) == NULL)
	{
		ft_putnbr(tree->stats.st_gid);
		ft_putchar(' ');
	}
	else
		put_mult_str(2, getgrgid(tree->stats.st_gid)->gr_name, " ");
	if (tree->ftr[0] != 'c' && tree->ftr[0] != 'b')
		ft_putnbr(tree->stats.st_size);
	else
	{
		ft_putnbr(major(tree->stats.st_rdev));
		ft_putnbr(minor(tree->stats.st_rdev));
	}
	ft_putchar(' ');
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
