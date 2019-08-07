/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_error_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:55:30 by ntom              #+#    #+#             */
/*   Updated: 2019/08/07 18:57:36 by ntom             ###   ########.fr       */
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
