/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <viforget@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:54:27 by viforget          #+#    #+#             */
/*   Updated: 2019/06/20 16:54:34 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	del_tree(t_info *tree)
{
	if (tree->left != NULL)
		del_tree(tree->left);
	if (tree->right != NULL)
		del_tree(tree->right);
	ft_strdel(&tree->name);
	ft_strdel(&tree->path);
	free(tree);
}

void	aff_tree(t_info *tree)
{
	if (tree->left != NULL)
		aff_tree(tree->left);
	ft_putendl(tree->name);
	if (tree->right != NULL)
		aff_tree(tree->right);
}

t_info	*noeud_stock(t_info *noeud, struct dirent *file, char *path)
{
		noeud = ft_memalloc(sizeof(t_info));
		noeud->name = file->d_name;
		noeud->path = ft_strjoin(path, noeud->name);
		noeud->type = file->d_type;
		noeud->status = lstat(noeud->path, &(noeud->stats));
		noeud->left = NULL;
		noeud->right = NULL;
		return(noeud);
}

static int	compare(int flags, t_info *first, t_info *second)
{
	if (is_on(flags, OPT_T))
	{
		if ((first->stats.st_mtime - second->stats.st_mtime) > 0)
			return (is_on(flags, OPT_R) ? 0 : 1);
		else if ((first->stats.st_mtime - second->stats.st_mtime) < 0)
			return (is_on(flags, OPT_R) ? 1 : 0);
	}
	if (ft_strcmp(first->name, second->name) < 0)
		return (is_on(flags, OPT_R) ? 0 : 1);
	return (is_on(flags, OPT_R) ? 1 : 0);
}

t_info	*bin_stock(t_info *tree, struct dirent *file, int flags, char *path)
{
	if (tree == NULL)
		tree = noeud_stock(tree, file, path);
	else if(/*comp*/1)
		tree->left = bin_stock(tree->left, file, flags, path);
	else
		tree->right = bin_stock(tree->left, file, flags, path);
	return (tree);
}


t_info	*create_tree(DIR *rep, int flags, char *path)
{
	struct dirent	*file;
	t_info			*tree;

	file = readdir(rep);
	while (file)
	{
		tree = bin_stock(tree, file, flags, path);
		file = readdir(rep);
	}
	return (tree);
}
