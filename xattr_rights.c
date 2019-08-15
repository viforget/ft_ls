/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr_rights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:50:23 by ntom              #+#    #+#             */
/*   Updated: 2019/08/16 00:17:14 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char		*ft_xattr(char *path)
{
	ssize_t	tmp;
	acl_t	acl;

	if ((tmp = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) > 0)
		return ("@");
	else if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)) != (acl_t)NULL)
	{
		acl_free((void*)acl);
		return ("+");
	}
	return (" ");
}

void		rights(int value, char ftr[12])
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
