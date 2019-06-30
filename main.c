/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/06/27 18:33:26 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

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

static void		sort_arg(char **argv, int flags, int argc)
{
	int				i;

	i = 0;
	while (i < argc - 1)
	{
		if (i < argc && argv[i][0] == '\0')
			return (ft_putendl("ft_ls: fts_open: No such file or directory"));
		if (compare(argv[i], argv[i + 1]) > 0 && is_off(flags, OPT_R))
		{
			ft_strswap(&argv[i], &argv[i + 1]);
			i = 0;
			continue ;
		}
		else if (r_compare(argv[i], argv[i + 1]) > 0 && is_on(flags, OPT_R))
		{
			ft_strswap(&argv[i], &argv[i + 1]);
			i = 0;
			continue ;
		}
		i++;
	}
}

void	ft_ls(char *st, int flags, char *path)
{
	t_info	*tree;
	DIR 	*dir;

	tree = NULL;
	dir = opendir(path);
	if (dir)
		tree = create_tree(dir, flags, path);
	else if (errno == ENOTDIR)
		ft_putendl(st);
	else
		put_mult_str(3, "ft_ls: ", st, ": No such file or directory");
	aff_tree(tree, flags);
	del_tree(tree, flags);
}

static void		ft_multi_ls(char **argv, int flags, int argc)
{
	int			i;

	i = 0;
	sort_arg(argv, flags, argc);
	while(i < argc)
	{
		ft_ls(argv[i], flags, argv[i]);
		i++;
	}
}

int				main(int argc, char **argv)
{
	int				flags;
	int				i;

	flags = 0;
	i = parsing(argv, &flags);
	if (i == argc)
		ft_ls(".", flags, ".");
	else
		ft_multi_ls(argv + i, flags, argc - i);
	return (0);
}
