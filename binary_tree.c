/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:54:27 by viforget          #+#    #+#             */
/*   Updated: 2019/08/07 18:03:53 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_info		*noeud_stock(t_info *noeud, char *file, char *path
	, unsigned int *blocks)
{
	struct stat		buf;
	char			*str;

	if (path[0] != '/' || path[1] != '\0')
		str = ft_strjoin(path, "/");
	else
		str = ft_strdup(path);
	noeud = ft_memalloc(sizeof(t_info));
	noeud->name = ft_strdup(file);
	noeud->path = ft_strjoin(str, noeud->name);
	ft_strdel(&str);
	noeud->status = lstat(noeud->path, &(buf));
	noeud->stats = buf;
	if (is_on(g_flags, OPT_L))
		stock_l(noeud);
	if (is_on(g_flags, OPT_L)
		&& (is_on(g_flags, OPT_A) || file[0] != '.'))
		*blocks += buf.st_blocks;
	noeud->left = NULL;
	noeud->right = NULL;
	return (noeud);
}

static int	compare(t_info *first, t_info *second, char err)
{
	if (err == FILES && is_on(g_flags, OPT_T))
	{
		if (first->stats.st_mtime > second->stats.st_mtime)
			return (is_on(g_flags, OPT_R) ? 1 : 0);
		else if (first->stats.st_mtime < second->stats.st_mtime)
			return (is_on(g_flags, OPT_R) ? 0 : 1);
	}
	if (ft_strcmp(first->name, second->name) < 0)
	{
		return (err == ERRORS || is_off(g_flags, OPT_R) ? 0 : 1);
	}
	return (err == ERRORS || is_off(g_flags, OPT_R) ? 1 : 0);
}

t_info		*bin_stock(t_info *tree, t_info *file, char err)
{
	if (tree == NULL)
		return (file);
	else if (compare(tree, file, err))
		tree->left = bin_stock(tree->left, file, err);
	else
		tree->right = bin_stock(tree->right, file, err);
	return (tree);
}

t_info		*create_tree(DIR *rep, char *path, unsigned int *blocks
	, size_t col[7])
{
	struct dirent	*dirr;
	t_info			*tree;
	t_info			*file;
	int				i;

	i = 1;
	while (i < 7)
		col[i++] = 0;
	col[0] = 11;
	tree = NULL;
	file = NULL;
	dirr = readdir(rep);
	while (dirr)
	{
		file = noeud_stock(tree, dirr->d_name, path, blocks);
		cnt_column(file, col);
		tree = bin_stock(tree, file, FILES);
		dirr = readdir(rep);
	}
	i = 1;
	add_column(col);
	return (tree);
}
