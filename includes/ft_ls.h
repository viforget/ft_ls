/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:04:05 by ntom              #+#    #+#             */
/*   Updated: 2019/06/16 19:36:51 by ntom             ###   ########.fr       */
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
** MACRO
*/

# define ON 1
# define OFF 0
# define OPT_L 0
# define OPT_MR 1
# define OPT_A 2
# define OPT_R 3
# define OPT_T 4


/*
** STRUCTURES
*/

typedef struct		s_info
{
	char 			*path;
	char			*name;
	struct stat		stats;
	struct s_info	*left;
	struct s_info	*right;
}					t_info;

/*
** MAIN.C
*/

/*
** PARSING.C
*/

int					parsing(char **argv, int *flags);

#endif
