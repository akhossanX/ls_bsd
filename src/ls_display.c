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

/*
**  @mode: file mode
**  @exec: flag indicating whether the file has execute/search permissions
**  @g_u_s_id: this flag contains setuid, setgid or sticky bit fields masks
*/

char    get_sticky(mode_t mode, mode_t exec, mode_t g_u_s_id)
{
    char    bit;

    if (exec == S_IXUSR || exec == S_IXGRP)
    {
        if ((mode & exec))
            bit = mode & g_u_s_id ? 's' : 'x';
        else
            bit = mode & g_u_s_id ? 'S' : '-';
    }
    else
    {
        if (mode & exec)
            bit = mode & g_u_s_id ? 't' : 'x';
        else
            bit = mode & g_u_s_id ? 'T' : '-';
    }
    return (bit);
}

char	*get_permissions(mode_t mode)
{
	static char	perm[10];

	perm[0] = (mode & S_IRUSR) ? 'r' : '-';
	perm[1] = (mode & S_IWUSR) ? 'w' : '-';
	perm[2] = get_sticky(mode, S_IXUSR, S_ISUID);
	perm[3] = (mode & S_IRGRP) ? 'r' : '-';
	perm[4] = (mode & S_IWGRP) ? 'w' : '-';
	perm[5] = get_sticky(mode, S_IXGRP, S_ISGID);
	perm[6] = (mode & S_IROTH) ? 'r' : '-';
	perm[7] = (mode & S_IWOTH) ? 'w' : '-';
	perm[8] = get_sticky(mode, S_IXOTH, S_ISVTX);
	return ((char *)perm);
}

void    print_month_day(char *datestr)
{
    static char month_day[7];

    ft_strncpy(month_day, datestr + 4, 6);
    ft_printf("%s ", month_day);
}

void    print_hour_min(t_ls *ls, t_path *entry, char *datestr, int is_modtime, time_t tim)
{
    time_t  current;

    if (is_modtime)
    {
        errno = 0;
        current = time(&current);
        if (errno && (ls->err = errno))
            ls_handle_error(ls, entry->name, get_error_level(ls->err));
        if (ft_abs(current - tim) > SIX_MONTHS)
        {
            write(1, " ", 1);
            write(1, datestr + 20, 4);
            return ;
        }
    }
    write(1, datestr + 11, 5);
}

//format returned by time function : "Thu Nov 24 18:22:48 1986\n\0"


void    print_date(t_ls *ls, t_path *lst)
{
    time_t  tim;
    char    *datestr;
    int     is_modtime;

	#ifdef __APPLE__
    tim = lst->st->st_mtimespec.tv_sec;
	#else
	tim = lst->st->st_mtim.tv_sec;
	#endif
    is_modtime = 1;
    if ((ls->options & OPT_C) && !(is_modtime = 0))
		#ifdef __APPLE__
        tim = lst->st->st_ctimespec.tv_sec;
		#else
		tim = lst->st->st_ctim.tv_sec;
		#endif
    else if ((ls->options & OPT_U) && !(is_modtime = 0))
		#ifdef __APPLE__
        tim = lst->st->st_atimespec.tv_sec;
		#else
		tim = lst->st->st_atim.tv_sec;
		#endif
    errno = 0;
    datestr = ctime(&tim);
    if (errno && (ls->err = errno))
        ls_handle_error(ls, NULL, get_error_level(ls->err));
    print_month_day(datestr);
    print_hour_min(ls, lst, datestr, is_modtime, tim);
}

void    print_entry(t_ls *ls, t_path *entry, char filetype)
{
    static char buff[256];

    ft_printf(" %s", entry->name);
    if (filetype == 'l')
    {
        if (readlink(entry->fullpath, buff, 255) == -1)
        {
            ls->err = errno;
            ls_handle_error(ls, entry->name, get_error_level(ls->err));
        }
        ft_printf(" -> %s", buff);
    }
    write(1, "\n", 1);
}

char    get_xattr_or_acl(t_ls *ls, t_path *path)
{
    ssize_t     size;
    acl_t       acl;
    acl_entry_t acl_entry;

    errno = 0;
    size = (path->xattrsz = listxattr(path->fullpath, NULL, 0, XATTR_NOFOLLOW));
    if (size > 0 && (ls->options & OPT_ATTR))
    {
        if (!(path->xattr = ft_strnew(size)) && (ls->err = errno))
            ls_handle_error(ls, path->name, get_error_level(ls->err));
        listxattr(path->fullpath, path->xattr, size, XATTR_NOFOLLOW);
    }
    acl = acl_get_file(path->fullpath, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry) == -1)
    {
        acl_free(acl);
        acl = NULL;
        ls_handle_error(ls, path->name, LS_MINOR_ERROR);
    }
    if (size > 0)
        return ('@');
    if (acl != NULL)
        return ('+');
    return (' ');
}

void    print_xattr(t_ls *ls, t_path *path)
{
    ssize_t size;
    char    *ptr;

    if (path->xattr)
    {
        ptr = path->xattr;
        while ((ptr - path->xattr) < path->xattrsz - 1)
        {
            errno = 0;
            size = getxattr(path->fullpath, ptr, NULL, 0, 0, XATTR_NOFOLLOW);
            if (size == -1)
            {
                ls->err = errno;
                ls_handle_error(ls, path->name, get_error_level(ls->err));
            }
            write(1, "\t", 1);
            write(1, ptr, ft_strlen(ptr));
            write(1, "\t", 1);
            ft_printf("%*d \n", ls->display.size_length, size);
            ptr = ft_strchr(ptr, 0) + 1;
        }
    }
}

void    long_display(t_ls *ls, t_path *path, int dir_or_files)
{
    int     onlysize_len;
    char    filetype;

    onlysize_len = ls->display.has_cbdev ? ls->display.size_length * 2 + 2 : 
            ls->display.size_length;
    dir_or_files == DIRECTORY ? ft_printf("total %d\n", ls->display.blocks) : 0;
    while (path != NULL)
    {
        ft_printf("%c", (filetype = get_filetype(path->st->st_mode & S_IFMT)));
		ft_printf("%s", get_permissions(path->st->st_mode));
        ft_printf("%c ", get_xattr_or_acl(ls, path));
        ft_printf("%*lld ", ls->display.lnk_length , path->st->st_nlink);
        if ((ls->options & OPT_G) == 0)
            ft_printf("%-*s  ", ls->display.owner_length, path->usrname);
        ft_printf("%-*s  ", ls->display.grp_length, path->grpname);
        if ((path->st->st_mode & S_IFMT) == S_IFBLK 
            || (path->st->st_mode & S_IFMT) == S_IFCHR)
            ft_printf("%*d, %*d ", ls->display.size_length, path->major,
                ls->display.size_length, path->minor);
        else
            ft_printf("%*d ", onlysize_len, path->st->st_size);
        print_date(ls, path);
        print_entry(ls, path, filetype);
        ls->options & OPT_ATTR ? print_xattr(ls, path) : 0;
        path = path->next;
    }
}

void    ls_display(t_ls *ls, t_path *lst, int dir_or_files)
{
    if ((ls->options & OPT_L) || (ls->options & OPT_G))
        long_display(ls, lst, dir_or_files);
    else if (ls->options & OPT_CAPC)
        block_display(ls, lst, dir_or_files);
    else
        one_column_display(lst);
}