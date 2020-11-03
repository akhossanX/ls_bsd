#include "ft_ls.h"

void    ls_display(t_ls *ls, t_path *lst)
{
    (void)ls;
    // Display it simple as for now
    while (lst)
    {
        ft_printf("%s\n", lst->name);
        lst = lst->next;
    }
}