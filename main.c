/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:20:05 by ntom              #+#    #+#             */
/*   Updated: 2019/06/20 12:36:49 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

// static void		init_tree(struct stat *buf, char *argv, t_info *i, char *path)
// {
// 	i->name = ft_strdup(argv);
// 	i->path = ft_strdup(path);
// 	i->status = lstat(argv, buf);
// 	i->stats = *buf;
// 	i->left = NULL;
// 	i->right = NULL;
// }

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

static void		ft_ls(char **argv, int flags, int argc)
{
	int			i;

	i = 0;
	sort_arg(argv, flags, argc);
	while (i < argc)
	{
		printf("argv[%i] == %s\n", i, argv[i]);
		i++;
	}
}

int				main(int argc, char **argv)
{
	int				flags;
	int				i;

	flags = 0;
	i = parsing(argv, &flags);
	ft_ls(argv + i, flags, argc - i);
	return (0);
}
