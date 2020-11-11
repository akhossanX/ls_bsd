#include "ft_ls.h"


void	filter_options(t_ls *ls, int flag)
{
	ls->options |= flag;
	if (flag == OPT_L)
	{
		ls->options & OPT_1 ? ls->options ^= OPT_1 : 0;
		ls->options & OPT_CAPC ? ls->options ^= OPT_CAPC : 0;
	}
	else if (flag == OPT_1)
	{
		ls->options & OPT_L ? ls->options ^= OPT_L : 0;
		ls->options & OPT_CAPC ? ls->options ^= OPT_CAPC : 0;
	}
	else if (flag == OPT_CAPC)
	{
		ls->options & OPT_L ? ls->options ^= OPT_L : 0;
		ls->options & OPT_1 ? ls->options ^= OPT_1 : 0;
	}
	flag == OPT_C && (ls->options & OPT_U) ? ls->options ^= OPT_U : 0;
	flag == OPT_U && (ls->options & OPT_C) ? ls->options ^= OPT_C : 0;
	flag == OPT_D && (ls->options & OPT_CAPR) ? ls->options ^= OPT_CAPR : 0;
	flag == OPT_F ? ls->options |= OPT_A : 0;
}


int		is_valid_option(const char opt)
{
	int		i;

	i = 0;
	while (i < NOPTIONS)
	{
		if (g_options[i].option == opt)
			return (g_options[i].code);
		i++;
	}
	return (0);
}

void		get_cli_options(t_ls *ls, char **argv)
{
	int		i;
	int		j;
	int		optcode;

	i = 0;
	while (argv[i] && !ft_strequ(argv[i], "--"))
	{
		if (*argv[i] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if ((optcode = is_valid_option(argv[i][j])))
					filter_options(ls, optcode);
				else
					ls_usage(ls, argv[i][j]);
				j++;
			}
		}
		i++;
	}
	if (argv[i])
		ls->optend = i;
}

void    parse_cli_arguments(t_ls *ls, char **av)
{
    int i;

	get_cli_options(ls, av);
    i = 0;
    while (av[i])
    {
        if (*av[i] != '-' || i > ls->optend)
        {
            ls->operands++;
            ls_save_path(ls, &ls->all, NOPARENT, av[i]);
        }
        i++;
    }
    if (ls->all == NULL && ls->operands == 0)
        ls_save_path(ls, &ls->all, NOPARENT, ".");
}