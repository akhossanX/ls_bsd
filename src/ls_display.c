#include "ft_ls.h"

void    one_column_display(t_path *lst)
{
    while (lst)
    {
		ft_printf("%s\n", lst->name);
        lst = lst->next;
    }
}

char    get_filetype(mode_t mode)
{
    if (mode == S_IFDIR)
        return ('d');
    if (mode == S_IFCHR)
        return ('c');
    if (mode == S_IFLNK)
        return ('l');
    if (mode == S_IFBLK)
        return ('b'); 
    if (mode == S_IFIFO)
        return ('p');
    if (mode == S_IFSOCK)
        return ('s');
    return ('-');
}

char	*get_permissions(mode_t mode)
{
	static char	perm[10];

	perm[0] = (mode & S_IRUSR) ? 'r' : '-';
	perm[1] = (mode & S_IWUSR) ? 'w' : '-';
	perm[2] = (mode & S_IXUSR) ? 'x' : '-';
	perm[3] = (mode & S_IRGRP) ? 'r' : '-';
	perm[4] = (mode & S_IWGRP) ? 'w' : '-';
	perm[5] = (mode & S_IXGRP) ? 'x' : '-';
	perm[6] = (mode & S_IROTH) ? 'r' : '-';
	perm[7] = (mode & S_IWOTH) ? 'w' : '-';
	perm[8] = (mode & S_IXOTH) ? 'x' : '-';
	return ((char *)perm);
}

void    long_display(t_ls *ls, t_path *lst, int dir_or_files)
{
    if (dir_or_files == DIRECTORY)
        ft_printf("total %d\n", ls->display.blocks);
    while (lst != NULL)
    {
        ft_printf("%c", get_filetype(lst->st->st_mode & S_IFMT));
		ft_printf("%s  ", get_permissions(lst->st->st_mode));
        ft_printf("%*lld ", ls->display.lnk_length , lst->st->st_nlink);
        ft_printf("%-*s  ", ls->display.owner_length, lst->usrname);
        ft_printf("%-*s  ", ls->display.grp_length, lst->grpname);
        ft_printf("<SIZE> ");
        ft_printf("<DATE> ");
        ft_printf("%s\n", lst->name);
        lst = lst->next;
    }
}

/*
**  Bonus
**  Dispaly the directory entries in block format
*/

void    block_display(t_ls *ls, t_path *lst)
{
    (void)ls, (void)lst;
}


void    ls_display(t_ls *ls, t_path *lst, int dir_or_files)
{
    if (ls->options & OPT_L)
        long_display(ls, lst, dir_or_files);
    else if (ls->options & OPT_CAPC)
        block_display(ls, lst);
    else
        one_column_display(lst);
}
