/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:40:59 by viforget          #+#    #+#             */
/*   Updated: 2019/08/06 18:26:30 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	setstr(char *bstr, char *str, int nbr)
{
	int i;

	i = ft_strlen(str) - 1;
	nbr--;
	while (i >= 0 && bstr[nbr] && str[i])
	{
		bstr[nbr] = str[i];
		i--;
		nbr--;
	}
}

void	setstr2(char *bstr, char *str, int nbr)
{
	int i;

	i = 0;
	nbr++;
	while (bstr[nbr] && str[i])
	{
		bstr[nbr] = str[i];
		i++;
		nbr++;
	}
}

char	*string_l(size_t col[7], t_info *node)
{
	char	*str;

	str = (char *)ft_memalloc(col[6] + 10);
	str = ft_memset(str, 32, col[6] + 9);
	setstr(str, node->ftr, col[0]);
	setstr(str, node->links, col[1] + 1);
	setstr2(str, node->uid, col[1] + 1);
	setstr2(str, node->grid, col[2] + 3);
	setstr(str, node->size_majmin, col[4] + 6);
	setstr2(str, node->month_day, col[4] + 6);
	setstr2(str, node->hour_year, col[5] + 7);
	return (str);
}

void	cnt_column(t_info *tree, size_t col[7])
{
	if (tree->links != NULL && col[1] < ft_strlen(tree->links))
		col[1] = ft_strlen(tree->links);
	if (tree->uid != NULL && col[2] < ft_strlen(tree->uid))
		col[2] = ft_strlen(tree->uid);
	if (tree->grid != NULL && col[3] < ft_strlen(tree->grid))
		col[3] = ft_strlen(tree->grid);
	if (tree->size_majmin != NULL && col[4] < ft_strlen(tree->size_majmin))
		col[4] = ft_strlen(tree->size_majmin);
	if (tree->month_day != NULL && col[5] < ft_strlen(tree->month_day))
		col[5] = ft_strlen(tree->month_day);
	if (tree->hour_year != NULL && col[6] < ft_strlen(tree->hour_year))
		col[6] = ft_strlen(tree->hour_year);
}
