/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:53:02 by ntom              #+#    #+#             */
/*   Updated: 2019/08/07 16:04:09 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"
#define _6MONTHS 15552000

char		*ft_xattr(char *path)
{
	ssize_t	tmp;
	acl_t	acl;

	if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)) != (acl_t)NULL)
	{
		acl_free((void*)acl);
		return ("+");
	}
	else if ((tmp = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) > 0)
		return ("@");
	return (" ");
}

static void	rights(int value, char ftr[12])
{
	ftr[1] = ((value & S_IRUSR) ? 'r' : '-');
	ftr[2] = ((value & S_IWUSR) ? 'w' : '-');
	if (value & S_ISUID)
		ftr[3] = ((value & S_IXUSR) ? 's' : 'S');
	else
		ftr[3] = ((value & S_IXUSR) ? 'x' : '-');
	ftr[4] = ((value & S_IRGRP) ? 'r' : '-');
	ftr[5] = ((value & S_IWGRP) ? 'w' : '-');
	if (value & S_ISGID)
		ftr[6] = ((value & S_IXGRP) ? 's' : 'l');
	else
		ftr[6] = ((value & S_IXGRP) ? 'x' : '-');
	ftr[7] = ((value & S_IROTH) ? 'r' : '-');
	ftr[8] = ((value & S_IWOTH) ? 'w' : '-');
	if (value & S_ISVTX)
		ftr[9] = ((value & S_IXOTH) ? 't' : 'T');
	else
		ftr[9] = ((value & S_IXOTH) ? 'x' : '-');
}

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

	str = (char *)malloc(sizeof(char) * 8);
	str = ft_memset(str, ' ', 8);
	tp = ft_itoa(major(rdev));
	i = ft_strlen(tp) - 1;
	j = 1;
	while (i >= 0)
		str[j--] = tp[i--];
	ft_strdel(&tp);
	tp = ft_itoa(minor(rdev));
	i = ft_strlen(tp) - 1;
	j = 6;
	while (i >= 0)
		str[j--] = tp[i--];
	str[2] = ',';
	str[7] = '\0';
	ft_strdel(&tp);
	return (str);
}

char		*set_zero(char **tmp)
{
	char *str;

	*tmp[10] = '\0';
	*tmp[16] = '\0';
	str = ft_strdup(*tmp + 4);
	*tmp[24] = '\0';
	return (str);
}

void		stock_l(t_info *node)
{
	char *tmp;

	tmp = NULL;
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
	tmp = ctime(&node->stats.st_mtime);
	node->month_day = set_zero(&tmp);
	if (time(NULL) < node->stats.st_mtime
		|| time(NULL) - node->stats.st_mtime > _6MONTHS)
		node->hour_year = ft_strdup(tmp + 20);
	else
		node->hour_year = ft_strdup(tmp + 11);
}
