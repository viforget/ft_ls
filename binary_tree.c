/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:54:27 by viforget          #+#    #+#             */
/*   Updated: 2019/06/20 16:32:50 by viforget         ###   ########.fr       */
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
		noeud = malloc(sizeof(t_info));
		noeud->name = file->d_name;
		noeud->path = ft_strjoin(path, noeud->name);
		noeud->type = file->d_type;
		noeud->status = lstat(noeud->path, &(noeud->stats));
		noeud->left = NULL;
		noeud->right = NULL;
		return(noeud);
}

t_info	*bin_stock(t_info *tree, struct dirent *file, unsigned int flag, char *path)
{
	if (tree == NULL)
		tree = noeud_stock(tree, file, path);
	else if(/*comp*/1)
		tree->left = bin_stock(tree->left, file, flag, path);
	else
		tree->right = bin_stock(tree->left, file, flag, path);
	return (tree);
}


t_info	*create_tree(DIR *rep, unsigned int flag, char *path)
{
	struct dirent	*file;
	t_info			*tree;

	file = readdir(rep);
	while (file)
	{
		tree = bin_stock(tree, file, flag, path);
		file = readdir(rep);
	}
	return (tree);
}
