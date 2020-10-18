
#include "ft_ls.h"

void    ls_files(t_ls *ls)
{
    if (ls->files)
    {
        if (!(ls->options & OPT_CAPU))
            ls->files = ls_sort(ls, ls->files);
        ls_display(ls, ls->files);
    }
}

void    ls_dirs(t_ls *ls)
{
    t_path  *ptr;

    if (!(ls->options & OPT_CAPU))
        ls->dirs = ls_sort(ls, ls->dirs);
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
    errno = 0;
    if (!(dp = opendir(entry)))
    {
        if (errno != ENOTDIR) // the error is not related to entry type (file ...)
            ft_dprintf(STDERR, "%s: %s: %s\n", ls->prog, dir->name, strerror(errno));
        ls->errcode = 1;
        return ;
    }
    lst = NULL;
    while (de = readdir(dp))
    {
        ft_ls_path_add(&lst, ft_ls_path_new(ls, de->d_name));
    }
    if (ls->dir_count > 1)
        ft_printf("%s:\n", entry);
    ft_strdel(&entry);
    if (!(ls->options & OPT_CAPU))
        lst = ls_sort(ls, lst);
    ls_display(ls, lst);
    t_path  *tmp;
    if (ls->options & OPT_CAPR)
    {
        while (lst)
        {
            ls_dir(ls, ls);
            tmp = lst;
            lst = lst->next;
            free(tmp);
        }
    }
}
