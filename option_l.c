/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:53:02 by ntom              #+#    #+#             */
/*   Updated: 2019/06/30 18:15:50 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

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

void		stock_l(t_info *noeud)
{
	noeud->ftr = ft_strdup(file_type(noeud->stats.st_mode));
	noeud->ftr = ft_strjoindel(noeud->ftr, ft_xattr(noeud->path));
}
