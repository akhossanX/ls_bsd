
#include "ft_ls.h"

void    ls_files(t_ls *ls)
{
    if (ls->files)
    {
        // ls->files = ls_sort(ls, ls->files);
        ls_display(ls, ls->files);
    }
}

void    ls_dirs(t_ls *ls)
{
    t_path  *ptr;

    // ls->dirs = ls_sort(ls, ls->dirs);
    if (ls->options & OPT_D)
        ls_display(ls, ls->dirs);
    else
    {
        ptr = ls->dirs;
        while (ptr)
        {
            ls_dir(ls, ptr);
            ptr = ptr->next;
        }
    }
}


void    ls_dir(t_ls *ls, t_path *dir)
{
    DIR *dp;
    char    *entry;
    struct dirent   *de;
    t_path  *lst;

    entry = make_full_path(dir->parent, dir->name);
    if (errno != 0)
        ft_ls_terminate(ls, errno);
    errno = 0;
    if ((dp = opendir(entry)) == NULL)
    {
        if (errno != ENOTDIR) // the error is not related to entry type (file ...)
        {
            ft_dprintf(STDERR, "%s: %s: %s\n", ls->prog, dir->name, strerror(errno));
        }
        ls->errcode = 1;
        ft_strdel(&entry);
        return ;
    }
    if (ls->dir_count > 1)
        ft_printf("\n%s:\n", entry);
    lst = NULL;
    while ((de = readdir(dp)))
    {
        ft_ls_path_add(&lst, ft_ls_path_new(ls, entry, de->d_name));
    }
    ft_strdel(&entry);
    // lst = ls_sort(ls, lst);
    ls_display(ls, lst);
    t_path  *tmp;
    if (ls->options & OPT_CAPR)
    {
        while (lst)
        {
            if (!ft_strequ(lst->name, ".") && !ft_strequ(lst->name, ".."))
                ls_dir(ls, lst);
            tmp = lst;
            lst = lst->next;
            free(tmp);
        }
    }
}
