#include "ft_ls.h"

void    ls_display(t_ls *ls, t_path *lst)
{
    // Display it simple as for now
    while (lst)
    {
		if (ls->dir_count)
			ft_printf("%s:\n", lst->name);
		ft_printf("%s\n", lst->name);
        lst = lst->next;
    }
}
