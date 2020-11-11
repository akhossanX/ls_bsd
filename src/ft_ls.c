
#include "ft_ls.h"

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
	(*ls)->options = 0;
	(*ls)->dirs = NULL;
	(*ls)->files = NULL;
	(*ls)->all = NULL;
	(*ls)->dir_count = 0;
	(*ls)->optend = INT_MAX;
	(*ls)->errcode = 0;
	(*ls)->operands = 0;
}

/*
**	For debugging
*/

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
/*
static void	print_all(t_ls *ls)
{
	if (ls->options & OPT_D)
	{
		print_paths(ls->all);
		return ;
	}	
	ft_printf("{red}DIRS:\n");
	print_paths(ls->dirs);
	ft_printf("{blue}FILES:{eoc}\n");
	print_paths(ls->files);
}
*/

int		main(int ac, char **av)
{
	t_ls	*ls;
	int		errcode;

	(void)ac;
	ls_init(&ls, av);
	parse_cli_arguments(ls, av + 1);
	ls->sort_type = get_sort_type(ls->options);
	ls_process_files(ls);
	ls_process_dirs(ls, &ls->dirs);
	ls_dirs(ls, ls->dirs, CLI_DIRS);
	//print_all(ls);
	errcode = (ls->errcode == ENOTDIR) ? 0 : get_error_level(ls->errcode);
	ls_clean_all(ls);
	return (errcode);
}
