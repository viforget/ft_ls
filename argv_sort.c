/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:51:39 by viforget          #+#    #+#             */
/*   Updated: 2019/08/06 16:02:10 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	sort_argv(char **argv, int argc, size_t col[7])
{
	int 	i;
	DIR		*buf;
	t_info	*tmp;
	t_info	*tre[3];

	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (ft_putendl("ft_ls: fts_open: No such file or directory"));
		tmp = noeud_stock(tmp, argv[i], "./", 0);
		cnt_column(tmp, col);
		if ((buf = opendir(argv[i])))
		{
			tre[0] = bin_stock(tmp, tre[0], FILES);
			closedir(buf);
		}
		else if (errno == ENOTDIR)
			tre[1] = bin_stock(tmp, tre[1], FILES);
		else
			tre[2] = bin_stock(tmp, tre[2], ERRORS);
		i++;
	}
	//aff_error(tre[2]);
}
