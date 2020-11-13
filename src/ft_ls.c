
#include "ft_ls.h"

t_sort	get_sort_type(int options)
{
	if (options & OPT_T)
	{
		if (options & OPT_U)
			return (ATIME_SORT);
		if (options & OPT_C)
			return (CTIME_SORT);
		return (MTIME_SORT);
	}
	if (options & OPT_CAPS)
		return (SIZE_SORT);
	if (options & OPT_F)
		return (NO_SORT);
	return (ASCII_SORT);
}

static void	ls_init(t_ls **ls, char **av)
{
	*ls = NULL;
	errno = 0;
	if (!(*ls = ft_memalloc(sizeof(t_ls))))
	{
		perror(av[0]);
		exit(errno);
	}
	(*ls)->prog = av[0];
	(*ls)->optend = INT_MAX;
}

/*********************************  For debugging *********************************************/

void	print_paths(t_path *lst)
{
	t_path	*p;

	p = lst;
	while (p)
	{
		ft_printf("%s\n", p->fullpath);
		p = p->next;
	}
}

void	print_all(t_ls *ls)
{	
	ft_printf("{red}DIRS:\n");
	print_paths(ls->dirs);
	ft_printf("{blue}FILES:\n");
	print_paths(ls->files);
	ft_printf("{eoc}");
}

/************************************************************************************************/


int		main(int ac, char **av)
{
	t_ls	*ls;
	int		errcode;

	(void)ac;
	ls_init(&ls, av);
	parse_cli_arguments(ls, av + 1);
	ls->sort_type = get_sort_type(ls->options);
	if (ls->sort_type != NO_SORT)
		ls->all = ls_sort(ls->all, ASCII_SORT, ls->options & OPT_R);
	process_arguments(ls);
	ls_cli_files(ls);
	ls_dirs(ls, ls->dirs, CLI);
	errcode = ls->ret;
	ls_clean_all(ls);
	return (errcode);
}
