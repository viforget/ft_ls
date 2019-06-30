/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:54:27 by viforget          #+#    #+#             */
/*   Updated: 2019/06/30 17:32:43 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_info		*noeud_stock(t_info *noeud, struct dirent *file, char *path)
{
	struct stat		buf;
	char			*str;

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

static int	compare(t_info *first, t_info *second)
{
	if (is_on(flags, OPT_T))
	{
		if (first->stats.st_mtime > second->stats.st_mtime)
			return (is_on(flags, OPT_R) ? 1 : 0);
		else if (first->stats.st_mtime < second->stats.st_mtime)
			return (is_on(flags, OPT_R) ? 0 : 1);
	}
	if (ft_strcmp(first->name, second->name) < 0)
		return (is_on(flags, OPT_R) ? 1 : 0);
	return (is_on(flags, OPT_R) ? 0 : 1);
}

t_info		*bin_stock(t_info *tree, t_info *file)
{
	if (tree == NULL)
		return (file);
	else if (compare(tree, file))
		tree->left = bin_stock(tree->left, file);
	else
		tree->right = bin_stock(tree->right, file);
	return (tree);
}

t_info		*create_tree(DIR *rep, char *path)
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
		tree = bin_stock(tree, file);
		dirr = readdir(rep);
	}
	return (tree);
}
