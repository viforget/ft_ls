/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:11:26 by ntom              #+#    #+#             */
/*   Updated: 2019/08/17 15:53:13 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void			aff_args(size_t col[7], t_info *files, t_info *directories)
{
	if (is_off(g_flags, OPT_A))
	{
		g_flags |= ON << OPT_A;
		aff_tree(files, col);
		g_flags &= ~(ON << OPT_A);
	}
	else
		aff_tree(files, col);
	if (directories != NULL)
		ft_putchar('\n');
}

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
