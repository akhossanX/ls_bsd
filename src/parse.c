#include "ft_ls.h"

void	filter_flags(t_ls *ls, int flag)
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
}

static void	ft_ls_validate_flags(t_ls *ls, char *flags)
{
	int		i;
	int		valid;

	while (*(++flags))
	{
		i = 0;
		valid = 0;
		while (i < OPTIONS)
		{
			if (g_options[i].option == *flags)
			{
				filter_flags(ls, g_options[i].code);
				valid = 1;
				break ;
			}
			i++;
		}
		if (!valid)
		{
			ft_dprintf(STDERR, "%s: invalid option -- '%c'\n", \
				ls->prog, *flags);
			ft_ls_terminate(ls, ERR_LS_INVOPT);
		}
	}
}

void	parse_cmd_line(t_ls *ls, char **av)
{
	int		i;
	int		opt_end;

	opt_end = INT_MAX;
	i = 0;
	while (av[i])
	{
		if (opt_end == INT_MAX && ft_strcmp(av[i], "--") == 0)
			opt_end = i;
		//else if (i < opt_end && ft_strncmp(av[i], "--", 2) == 0)
			//lookup_long_opt_table(cat, s[cat->i]);
		else if (i < opt_end && av[i][0] == '-' && av[i][1])
			ft_ls_validate_flags(ls, av[i]);
		else
		{
			ls->operands++;
			ft_ls_get_path(ls, av[i]);
		}
		i += 1;
	}
	if (ls->operands == 0)
		ft_ls_get_path(ls, ".");
}
