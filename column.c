/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:40:59 by viforget          #+#    #+#             */
/*   Updated: 2019/07/31 20:45:04 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	init_null(size_t *(col[7]))
{
	int i;

	i = 1;
	while(i < 7)
	{
		*col[i++] = 0;
	}
}

void	cnt_column(t_info* tree, size_t (*col)[7])
{
	if (*col[1] < ft_strlen(tree->links))
		*col[1] = ft_strlen(tree->links);
	if (*col[2] < ft_strlen(tree->uid))
		*col[2] = ft_strlen(tree->uid);
	if (*col[3] < ft_strlen(tree->grid))
		*col[3] = ft_strlen(tree->grid);
	if (*col[4] < ft_strlen(tree->size))
		*col[4] = ft_strlen(tree->size);
	if (*col[5] < ft_strlen(tree->month_day))
		*col[5] = ft_strlen(tree->month_day);
	if (*col[6] < ft_strlen(tree->hour_year))
		*col[6] = ft_strlen(tree->hour_year);
}
