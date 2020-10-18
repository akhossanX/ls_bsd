
#include "ft_ls.h"

static void	ls_init(t_ls **ls, char **av)
{
	if (!(*ls = ft_memalloc(sizeof(t_ls))))
		ft_ls_terminate(NULL, errno);
	(*ls)->prog = av[0];
	(*ls)->options = 0;
	(*ls)->dirs = NULL;
	(*ls)->files = NULL;
	(*ls)->dir_count = 0;
	(*ls)->errcode = 0;
	(*ls)->operands = 0;
}

static void	print_all(t_ls *ls)
{
	ft_printf("{red}DIRS\n");
	print_paths(ls->dirs);
	ft_printf("{blue}FILES{eoc}\n");
	print_paths(ls->files);
}

int		main(int ac, char **av)
{
	t_ls	*ls;

	(void)ac;
	ls = NULL;
	ls_init(&ls, av);
	parse_cmd_line(ls, av + 1);
	print_all(ls);
	ls_files(ls);
	ft_printf("dirs number: %d\n", ls->dir_count);
	ft_ls_terminate(ls, 0);
	return (0);
}
