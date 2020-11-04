#include "ft_ls.h"

char    *get_full_path(const char *parent, const char *entry)
{
    char    *fullpath;
    char    *tmp;

    errno = 0;
    if (ft_strlen(parent) == 0)
        return (ft_strdup(entry));
    if (!(tmp = ft_strjoin(parent, "/")))
        return (NULL);
    fullpath = ft_strjoin(tmp, entry);
    ft_strdel(&tmp);
    return (fullpath);
}

t_path  *ls_get_dir_content(t_ls *ls, t_path *dir)
{
    char            *fullpath;
    t_path          *content;
    DIR             *dp;
    struct dirent   *de;
    t_path          *entry;

    errno = 0;
    if (!(fullpath = get_full_path(dir->parent, dir->name)))
    {
        ls->errcode = errno;
        return (NULL);
    }
    if (dp = ls_opendir(ls, fullpath))
    {
        // read the directory and return a list of all the entries inside the directory
        // the list contains nodes representing each entry and its parent directory
    }
    return (NULL);
}

/*
**  opens the stream refered to by dipath
**  if the error is something else other that being a file it reports the error and returns null
**  otherwise it returns the directory stream pointer dp
*/

DIR     *ls_opendir(t_ls *ls, const char *dirpath)
{
    DIR *dp;

    errno = 0;
    dp = opendir(dirpath);
    if (dp == NULL && errno != ENOTDIR)
    {
        if (errno == ENOMEM)
        {
            ls->errcode = errno;
            return (NULL);
        }
        ft_dprintf(STDERR, "%s: %s: %s", ls->prog, dirpath, strerror(errno));
    }
    return (dp);
}

int     is_dir(t_ls *ls, const char *dirpath)
{

}