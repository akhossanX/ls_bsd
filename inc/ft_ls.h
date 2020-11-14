/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:55:17 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/09 10:22:34 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define NOPTIONS		15

# define LS_SUCCESS		0
# define LS_MINOR_ERROR	1
# define LS_MAJOR_ERROR	2
# define CLI			0
# define RECURSE		1
# define NOPARENT		NULL
# define FILES			0
# define DIRECTORY		1
# define SIX_MONTHS		15778800

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

# define OPT_F		(1 << 11)	/* Do not sort, list in directory order, and activate -a option */
# define OPT_C		(1 << 12)	/* Sort by ctime. with -lt sort and show ctime, with -l show ctime */
								/*	otherwise sort by ctime. */

# define OPT_CAPC	(1 << 13)	/* Use block display format */
# define OPT_CAPS	(1 << 14)	/* Sort by file size, largest first */



/*
**	Data structures
*/

typedef enum	e_sort
{
	ASCII_SORT,
	ATIME_SORT,
	CTIME_SORT,
	MTIME_SORT,
	SIZE_SORT,
	NO_SORT
}				t_sort;

typedef struct		s_option
{
	char	option;
	short	code;
}					t_option;

extern const t_option	g_options[];

typedef struct		s_path
{
	char			*name;
	char			*fullpath;
	struct stat		*st;
	struct passwd	*usrinfo;
	char			*usrname;
	struct group	*grpinfo;
	char			*grpname;
	int32_t			major;
	int32_t			minor;
	struct s_path	*next;
}					t_path;

typedef int64_t	(*t_cmp)(t_path *a, t_path *b, t_sort sort_type);

typedef struct		s_display
{
	int				lnk_length;
	int				owner_length;
	int				grp_length;
	int				blocks;
	int				size_length;
	int				has_cbdev;
	time_t			time;
}					t_display;

typedef struct		s_ls
{
	int16_t			options;
	int				err;
	int				ret; // the code to be returned on program exit
	int				operands;
	int				optend;
	t_sort			sort_type;
	t_display		display;
	struct dirent	*de;
	DIR				*dp;
	const char		*prog;
	t_path			*all;//all command line operands (non options)
	t_path			*dirs;
	t_path			*files;
}					t_ls;

void	parse_cli_arguments(t_ls *ls, char **av);
void	get_cli_options(t_ls *ls, char **av);
void	get_cli_operand(t_ls *ls, const char *arg);
void	ls_usage(t_ls *ls, const char option);
t_path	*ls_save_path(
		t_ls *ls, t_path **lst, const char *parent, const char *name);
void	ls_handle_error(t_ls *ls, const char *arg, int error_level);
int		get_error_level(int error);
void	ls_clean_all(t_ls *ls);
int		set_stat(t_ls *ls, t_path *target_list);

t_path	*ls_sort(t_path *target, t_sort sort_type, int order);
void	ls_display(t_ls *ls, t_path *list, int dir_or_files);

void	process_arguments(t_ls *ls);

void	ls_dirs(t_ls *ls, t_path *dirs, int cli_or_recurse);
void	ls_cli_files(t_ls *ls);

t_path	*ls_path_new(t_ls *ls, const char *parent, const char *name);
void	ls_path_append(t_path **lst, t_path *path);

void	ls_free_paths(t_path *lst);
void	ls_closedir(DIR **dirp);
int		ls_is_dir(t_ls *ls, const char *entry);

t_sort	get_sort_type(int option);

char	*get_full_path(const char *parent, const char *entry);


void	print_all(t_ls *ls);




#endif
