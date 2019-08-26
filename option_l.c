/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:53:02 by ntom              #+#    #+#             */
/*   Updated: 2019/08/26 16:21:19 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#define _6MONTHS 15552000

char		*file_type(int value)
{
	char		*ftr;

	if (!(ftr = ft_memalloc(sizeof(char) * 12)))
		return (NULL);
	if (value >= WHITEOUT)
		ftr[0] = 'w';
	else if (value >= SOCKLNK)
		ftr[0] = 's';
	else if (value >= SYMBLNK)
		ftr[0] = 'l';
	else if (value >= REGULAR)
		ftr[0] = '-';
	else if (value >= BLOCKSPE)
		ftr[0] = 'b';
	else if (value >= DIRECTOR)
		ftr[0] = 'd';
	else if (value >= CHARSPE)
		ftr[0] = 'c';
	else
		ftr[0] = 'p';
	rights(value, ftr);
	ftr[11] = '\0';
	return (ftr);
}

char		*majmin(dev_t rdev)
{
	char	*str;
	char	*tp;
	int		i;
	int		j;

	if (!(str = (char *)malloc(sizeof(char) * 8))
	|| !(tp = ft_itoa(major(rdev))))
		return (NULL);
	str = ft_memset(str, ' ', 8);
	i = ft_strlen(tp) - 1;
	j = 1;
	while (i >= 0)
		str[j--] = tp[i--];
	ft_strdel(&tp);
	if (!(tp = ft_itoa(minor(rdev))))
		return (NULL);
	i = ft_strlen(tp) - 1;
	j = 6;
	while (i >= 0)
		str[j--] = tp[i--];
	str[2] = ',';
	str[7] = '\0';
	ft_strdel(&tp);
	return (str);
}

static void	option_l2(t_info *node)
{
	node->ftr = file_type(node->stats.st_mode);
	node->ftr = ft_strjoindel(node->ftr, ft_xattr(node->path));
	node->links = ft_itoa(node->stats.st_nlink);
	if (getpwuid(node->stats.st_uid) == NULL)
		node->uid = ft_itoa(node->stats.st_uid);
	else
		node->uid = ft_strdup(getpwuid(node->stats.st_uid)->pw_name);
	if (getgrgid(node->stats.st_gid) == NULL)
		node->grid = ft_itoa(node->stats.st_gid);
	else
		node->grid = ft_strdup(getgrgid(node->stats.st_gid)->gr_name);
	if (node->ftr[0] != 'c' && node->ftr[0] != 'b')
		node->size_majmin = ft_itoa(node->stats.st_size);
	else
		node->size_majmin = majmin(node->stats.st_rdev);
}

int			stock_l(t_info *node)
{
	char *tmp;

	tmp = NULL;
	option_l2(node);
	if (!(node->ftr) || !(node->links) || !(node->uid)
	|| !(node->grid) || !(node->size_majmin))
		return (1);
	tmp = ctime(&node->stats.st_mtime);
	tmp[10] = '\0';
	tmp[16] = '\0';
	node->month_day = ft_strdup(tmp + 4);
	tmp[24] = '\0';
	if (time(NULL) < node->stats.st_mtime
		|| time(NULL) - node->stats.st_mtime > _6MONTHS)
		node->hour_year = ft_strdup(tmp + 20);
	else
		node->hour_year = ft_strdup(tmp + 11);
	if (!(node->month_day) || !(node->hour_year))
		return (1);
	return (0);
}
