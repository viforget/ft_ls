/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:40:59 by viforget          #+#    #+#             */
/*   Updated: 2019/08/01 15:14:55 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	init_null(size_t col[7])
{
	int i;

	i = 1;
	while (i < 7)
	{
		col[i++] = 0;
	}
}

void	cnt_column(t_info *tree, size_t col[7])
{
	if (tree->links != NULL && col[1] < ft_strlen(tree->links))
		col[1] = ft_strlen(tree->links);
	if (tree->uid != NULL && col[2] < ft_strlen(tree->uid))
		col[2] = ft_strlen(tree->uid);
	if (tree->grid != NULL && col[3] < ft_strlen(tree->grid))
		col[3] = ft_strlen(tree->grid);
	if (tree->size != NULL && col[4] < ft_strlen(tree->size))
		col[4] = ft_strlen(tree->size);
	if (tree->month_day != NULL && col[5] < ft_strlen(tree->month_day))
		col[5] = ft_strlen(tree->month_day);
	if (tree->hour_year != NULL && col[6] < ft_strlen(tree->hour_year))
		col[6] = ft_strlen(tree->hour_year);
}
