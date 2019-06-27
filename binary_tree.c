/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:54:27 by viforget          #+#    #+#             */
/*   Updated: 2019/06/27 18:33:56 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void		del_tree(t_info *tree, int flag)
{
	if (tree->left != NULL)
		del_tree(tree->left, flag);
	if (tree->right != NULL)
		del_tree(tree->right, flag);
	ft_strdel(&tree->name);
	ft_strdel(&tree->path);
	free(tree);
}

void		aff_tree(t_info *tree)
{
	if (tree->left != NULL)
		aff_tree(tree->left);
	ft_putendl(tree->name);
	if (tree->right != NULL)
		aff_tree(tree->right);
}

t_info		*noeud_stock(t_info *noeud, struct dirent *file, char *path)
{
	struct stat		buf;

	noeud = ft_memalloc(sizeof(t_info));
	noeud->name = ft_strdup(file->d_name);
	noeud->path = ft_strjoin(path, noeud->name);
	noeud->type = file->d_type;
	noeud->status = lstat(noeud->path, &(buf));
	noeud->stats = buf;
	noeud->left = NULL;
	noeud->right = NULL;
	return (noeud);
}

static int	compare(int flags, t_info *first, t_info *second)
{
	if (is_on(flags, OPT_T))
	{
		if ((first->stats.st_mtime - second->stats.st_mtime) > 0)
			return (is_on(flags, OPT_R) ? 1 : 0);
		else if ((first->stats.st_mtime - second->stats.st_mtime) < 0)
			return (is_on(flags, OPT_R) ? 0 : 1);
		if (ft_strcmp(first->name, second->name) < 0)
			return (is_on(flags, OPT_R) ? 1 : 0);
		return (is_on(flags, OPT_R) ? 1 : 0);
	}
	if (ft_strcmp(first->name, second->name) < 0)
		return (is_on(flags, OPT_R) ? 1 : 0);
	return (is_on(flags, OPT_R) ? 0 : 1);
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
		file = noeud_stock(tree, dirr, path);
		tree = bin_stock(tree, file, flags);
		dirr = readdir(rep);
	}
	return (tree);
}

/*
int			main(void)
{
	DIR				*dir;
	t_info			*tree;
	char			ftr[12];

	dir = opendir(".");
	tree = create_tree(dir, 0, "./");
	file_type(tree->stats.st_mode, ftr);
	//aff_tree(tree);
}
*/
