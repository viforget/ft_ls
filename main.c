/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/08/02 17:29:04 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void			ft_ls(char *st, char *path)
{
	t_info			*tree;
	DIR				*dir;
	unsigned int	blocks;
	size_t			col[7];

	tree = NULL;
	blocks = 0;
	dir = opendir(path);
	if (dir)
	{
		tree = create_tree(dir, path, &blocks, col);
		closedir(dir);
		if (is_on(g_flags, OPT_L))
		{
			ft_putstr("total ");
			ft_putnbr(blocks);
			ft_putchar('\n');
		}
		aff_tree(tree, col);
		del_tree(tree);
	}
	/*else if (errno == ENOTDIR)
		ft_putendl(st);
	else
	{
		put_mult_str(3, "ft_ls: ", st, ": No such file or directory\n");
		return ;
	}*/
}

t_info		*create_tree_no_arg(char **argv, unsigned int *blocks
	, size_t col[7])
{
	t_info			*tree;
	t_info			*file;
	int				i;
	DIR				*dir;

	i = 1;
	while(i < 7)
		col[i++] = 0;
	col [0] = 11;
	tree = NULL;
	file = NULL;
	i = 0;
	while (argv[i])
	{
		if ((dir = opendir(argv[i])))
		{}
		else if (errno == ENOTDIR)
		{
			file = noeud_stock(tree, argv[i], "./", blocks);
			cnt_column(file, col);
			tree = bin_stock(tree, file);
		}
		else
			put_mult_str(3, "ft_ls: ", st, ": No such file or directory\n");
		i++;
	}
	i = 1;
	while(i < 7)
	{
		col[i] += col[i - 1];
		i++;
	}
	return (tree);
}

static int		ft_isdir(char *current)
{
	struct stat		buf;

	if (lstat(current, &buf) == -1)
		return (0);
	return (S_ISDIR(buf.st_mode));
}

static int		compare(char *current, char *next)
{
	struct stat		buf;
	int				ret_current;
	int				ret_next;

	ret_current = lstat(current, &buf);
	ret_next = lstat(next, &buf);
	if (ret_current < ret_next)
		return (-1);
	else if (ret_current > ret_next)
		return (1);
	if (ft_isdir(current) && ft_isdir(next) == 0)
		return (1);
	else if (ft_isdir(next) && ft_isdir(current) == 0)
		return (-1);
	return (ft_strcmp(current, next));
}

static int		r_compare(char *current, char *next)
{
	struct stat		buf;
	int				ret_current;
	int				ret_next;

	ret_current = lstat(current, &buf);
	ret_next = lstat(next, &buf);
	if (ret_current < ret_next)
		return (-1);
	else if (ret_current > ret_next)
		return (1);
	if (ft_isdir(current) && ft_isdir(next) == 0)
		return (1);
	else if (ft_isdir(next) && ft_isdir(current) == 0)
		return (-1);
	else if (ret_current == -1)
		return (ft_strcmp(current, next));
	return (-ft_strcmp(current, next));
}

static void		sort_arg(char **argv, int argc)
{
	int				i;

	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (ft_putendl("ft_ls: fts_open: No such file or directory"));
		if (argv[i + 1]
			&& compare(argv[i], argv[i + 1]) > 0
			&& is_off(g_flags, OPT_R))
		{
			ft_strswap(&argv[i], &argv[i + 1]);
			i = 0;
			continue ;
		}
		else if (argv[i + 1]
			&& r_compare(argv[i], argv[i + 1]) > 0
			&& is_on(g_flags, OPT_R))
		{
			ft_strswap(&argv[i], &argv[i + 1]);
			i = 0;
			continue ;
		}
		printf("argv[%d] == %s\n", i, argv[i]);
		i++;
	}
}

static void		ft_multi_ls(char **argv, int argc)
{
	size_t			col[7];
	unsigned int	blocks;
	t_info			*tree;

	blocks = 0;
	sort_arg(argv, argc);
	tree = create_tree_no_arg(argv, &blocks, col);
	if (is_on(g_flags, OPT_L))
	{
		ft_putstr("total ");
		ft_putnbr(blocks);
		ft_putchar('\n');
	}
	aff_tree(tree, col);
	del_tree(tree);
}

int				main(int argc, char **argv)
{
	int				i;

	g_flags = 0;
	i = parsing(argv);
	if (i == argc)
		ft_ls(".", ".");
	else
	{
		ft_multi_ls(argv + i, argc - i);
	}
	return (0);
}
