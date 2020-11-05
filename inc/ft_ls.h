
#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <limits.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <assert.h>

# define OPTIONS		(15)
# define MAX_PATH_LEN	(255)

# define ERR_LS_INVOPT	(-1)

/*
**	Mandatory Options
*/

# define OPT_L		(1 << 0)	/* Long listing display format */
# define OPT_1		(1 << 1)	/* one column display format */
# define OPT_R		(1 << 2)	/* List entries in reverse order (whatever the sorting criteria is) */
# define OPT_CAPR	(1 << 3)	/* Recursive listing */
# define OPT_A		(1 << 4)	/* do not ignore entries with . */
# define OPT_T		(1 << 5)	/* Sort entries by modification time newest first */

/*
**	Bonus Options
*/

# define OPT_CAPA	(1 << 6)	/* Do not list implied . and .. */
# define OPT_G		(1 << 7)	/* Like -l but do not list owner */
# define OPT_CAPG	(1 << 8)	/* Enable Colorized output */
# define OPT_D		(1 << 9)	/* List directories themselves, not their content */
# define OPT_U		(1 << 10)	/* Sort by access time. with -lt sort and show access time, */
								/*	with -l show access time. */

# define OPT_F		(1 << 11)	/* Do not sort, list in directory order, and activate -a options */
# define OPT_C		(1 << 12)	/* Sort by ctime. with -lt sort and show ctime, with -l show ctime */
								/*	otherwise sort by ctime. */

# define OPT_CAPC	(1 << 13)	/* Use block display format */
# define OPT_CAPS	(1 << 14)	/* Sort by file size, largest first */

/*
**	Data structures
*/

typedef struct		s_option
{
	char	option;
	short	code;
}					t_option;

extern const t_option	g_options[];

typedef struct		s_path
{
	char			*name;
	char			*parent;
	struct s_path	*next;
}					t_path;

typedef int	(*t_cmp)(t_path *a, t_path *b, int flg);

typedef struct		s_ls
{
	int16_t			options;
	int				dir_count;//command line directories counter
	int				errcode;
	int				operands;
	int				optend;
	struct dirent	*de;
	DIR				*dp;
	const char		*prog;
	t_path			*all;//all command line operands (non options)
	t_path			*dirs;
	t_path			*files;
}					t_ls;

void	parse_cli_arguments(t_ls *ls, char **av);
void	get_cli_options(t_ls *ls, char **av);
void	ls_usage(t_ls *ls, const char option);

#endif
