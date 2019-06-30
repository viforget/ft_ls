/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:54:27 by viforget          #+#    #+#             */
/*   Updated: 2019/06/30 16:59:49 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		del_tree(t_info *tree, int flags)
{
	if (tree->left != NULL)
		del_tree(tree->left, flags);
	if (is_on(flags, OPT_UR) && tree->type == 4 && ft_strcmp(tree->name, ".") != 0
			&& ft_strcmp(tree->name, "..") != 0
			&& (is_on(flags, OPT_A) || tree->name[0] != '.'))
	{
		put_mult_str(3, "\n", tree->path, ":");
		ft_ls(tree->name, flags, tree->path);
	}
	if (tree->right != NULL)
		del_tree(tree->right, flags);
	ft_strdel(&tree->name);
	ft_strdel(&tree->path);
	ft_strdel(&tree->ftr);
	free(tree);
}

void		aff_tree(t_info *tree, int flags)
{
	if (tree->left != NULL)
		aff_tree(tree->left, flags);
	if (is_on(flags, OPT_A) || tree->name[0] != '.')
		put_mult_str(3, tree->ftr, " ", tree->name);
	if (tree->right != NULL)
		aff_tree(tree->right, flags);
}

static char	*ft_xattr(char *path)
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

static void	stock_l(t_info *noeud)
{
	noeud->ftr = ft_strdup(file_type(noeud->stats.st_mode));
	noeud->ftr = ft_strjoindel(noeud->ftr, ft_xattr(noeud->path));
}

t_info		*noeud_stock(t_info *noeud, struct dirent *file, char *path, int flags)
{
	struct stat		buf;
	char *str;

	str = ft_strjoin(path, "/");
	noeud = ft_memalloc(sizeof(t_info));
	noeud->name = ft_strdup(file->d_name);
	noeud->path = ft_strjoin(str, noeud->name);
	ft_strdel(&str);
	noeud->type = file->d_type;
	noeud->status = lstat(noeud->path, &(buf));
	noeud->stats = buf;
	if (is_on(flags, OPT_L))
		stock_l(noeud);
	noeud->left = NULL;
	noeud->right = NULL;
	return (noeud);
}

static int	compare(int flags, t_info *first, t_info *second)
{
	if (is_on(flags, OPT_T))
	{
		if (first->stats.st_mtime > second->stats.st_mtime)
			return (is_on(flags, OPT_R) ? 1 : 0);
		else if (first->stats.st_mtime < second->stats.st_mtime)
			return (is_on(flags, OPT_R) ? 0 : 1);
		if (ft_strcmp(first->name, second->name) < 0)
			return (is_on(flags, OPT_R) ? 1 : 0);
		return (is_on(flags, OPT_R) ? 0 : 1);
	}
	if (ft_strcmp(first->name, second->name) < 0)
		return (is_on(flags, OPT_R) ? 0 : 1);
	return (is_on(flags, OPT_R) ? 1 : 0);
}

t_info		*bin_stock(t_info *tree, t_info *file, int flags)
{
	if (tree == NULL)
		return (file);
	else if (compare(flags, tree, file))
		tree->left = bin_stock(tree->left, file, flags);
	else
		tree->right = bin_stock(tree->right, file, flags);
	return (tree);
}

t_info		*create_tree(DIR *rep, int flags, char *path)
{
	struct dirent	*dirr;
	t_info			*tree;
	t_info			*file;

	tree = NULL;
	file = NULL;
	dirr = readdir(rep);
	while (dirr)
	{
		file = noeud_stock(tree, dirr, path, flags);
		tree = bin_stock(tree, file, flags);
		dirr = readdir(rep);
	}
	return (tree);
}
