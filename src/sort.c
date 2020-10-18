#include "ft_ls.h"

static t_path   *sort(t_ls *ls, t_path *entries)
{
    
}

t_path  *ls_sort(t_ls *ls, t_path *entries)
{
    if (ls->options & OPT_R)
        return (reverse_sort(ls, entries));
    return (sort(ls, entries));
}
