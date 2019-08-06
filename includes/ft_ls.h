/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:04:05 by ntom              #+#    #+#             */
/*   Updated: 2019/08/06 19:38:20 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** LIBRARIES
*/

# include "../libft/libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <dirent.h>
# include <time.h>
# include <grp.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <uuid/uuid.h>

/*
** OPTION MACROS
*/

# define ON 1
# define OFF 0
# define OPT_L 0
# define OPT_UR 1
# define OPT_A 2
# define OPT_R 3
# define OPT_T 4

/*
** TYPES MACROS
*/

# define WHITEOUT 57344
# define SOCKLNK 49152
# define SYMBLNK 40960
# define REGULAR 32768
# define BLOCKSPE 24576
# define DIRECTOR 16384
# define CHARSPE 8192

/*
** OTHER MACROS
*/

# define FILES 0
# define ERRORS 1

/*
** GLOBAL
*/

int					g_flags;

/*
** STRUCTURES
*/

typedef struct		s_info
{
	char			*path;
	char			*name;
	struct stat		stats;
	int				status;
	char			*ftr;
	char			*links;
	char			*uid;
	char			*grid;
	char			*size_majmin;
	char			*month_day;
	char			*hour_year;
	struct s_info	*left;
	struct s_info	*right;
}					t_info;

/*
** MAIN.C
*/

void				ft_ls(char *st, char *path);

/*
** PARSING.C
*/

int					parsing(char **argv);

/*
** OPTION_L.C
*/

char				*ft_xattr(char *path);
char				*file_type(int value);
void				stock_l(t_info *noeud);

/*
** BINARY_TREE.C
*/

t_info				*create_tree(DIR *rep, char *path, unsigned int *blocks,
	size_t col[7]);
t_info				*bin_stock(t_info *tree, t_info *file, char err);
t_info				*noeud_stock(t_info *noeud, char *file, char *path,
	unsigned int *blocks);

/*
** AFF_DEL_TREE.C
*/

void				del_tree(t_info *tree);
void				aff_tree(t_info *tree, size_t col[7]);

/*
** COLUMN.C
*/

char				*string_l(size_t col[7], t_info *node);
void				cnt_column(t_info *tree, size_t col[7]);
void				add_column(size_t col[7]);

/*
** ARGV_SORT.C
*/

void				sort_argv(char **argv, int argc, size_t col[7]);

#endif
