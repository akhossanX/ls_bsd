
#include "ft_ls.h"

static void	ls_init(t_ls **ls, char **av)
{
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
		ft_printf("%s\n", p->name);
		p = p->next;
	}
}

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

int		main(int ac, char **av)
{
	t_ls	*ls;

	(void)ac;
	ls = NULL;
	ls_init(&ls, av);
	parse_cli_arguments(ls, av + 1);
	ft_printf("flags: %015b\n", ls->options);

	print_all(ls);
	ls_clean_all(ls);
	//ls_files(ls);
	//ls_dirs(ls);
	//ft_printf("\n\n\ndirs number: %d\n", ls->dir_count);
	//ft_ls_terminate(ls, 0);
	return (0);
}
