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

/*
**	Closes the directory stream if it is already opened
**	and sets the pointer to null
*/

void	ft_ls_closedir(DIR **dirp)
{
	if (*dirp != NULL)
		(void)closedir(*dirp);
	*dirp = NULL;
}

/*
**	Reads the content of a directory stream and returns its content
**	On error it returns NULL and sets ls->errcode according to errno
*/

t_path	*ls_readdir(t_ls *ls, const char *dir)
{
	t_path	*dir_content_list;
	t_path	*entry;

	dir_content_list = NULL;
	while ((ls->de = readdir(ls->dp)) != NULL)
	{
		if (!(entry = ft_ls_path_new(ls, dir, ls->de->d_name)))
			return (NULL);
		ft_ls_path_add(&dir_content_list, entry);
	}
	if (ls->de == NULL && errno)
	{
		ls->errcode = errno;
		free_paths(dir_content_list);
		return (NULL);
	}
	ft_ls_closedir(ls->dp);
	return (dir_content_list);
}

/*
**	Opens a directory streams, reads its content and stores it
**	in a list of paths (directory entries)
**	On error it returns NULL and sets ls->errcode appropriately
**	this ls->errcode is fetched later, based on the level of danger,
**	we decide what to do accordingly.
*/

t_path  *ls_get_dir_content(t_ls *ls, t_path *dir)
{
    char            *fullpath;
    t_path          *content;
    t_path          *entry;

    errno = 0;
    if (!(fullpath = get_full_path(dir->parent, dir->name)))
    {
        ls->errcode = errno;
        return (NULL);
    }
    if (ls->dp = ls_opendir(ls, fullpath))
    {
		content = ls_readdir(ls, fullpath);
		ft_strdel(&fullpath);
		return (content);
    }
	else
		ls->errcode = errno; // Check later which type of error has taken place
    return (NULL);
}

int		ft_ls_dir(t_ls *ls, t_path *dir)
{
	t_path	*dir_content_list;

	dir_content_list = ls_get_dir_content(ls, dir);
	if (dir_content_list != NULL)
	{
		// list the fucking directory content with the requested informations
		return (1);	
	}
	return (0);
}


int		ft_ls_cli_dirs(t_ls *ls)
{
	t_path	*dir;

	dir = ls->dirs;
	while (dir != NULL)
	{
		if (ft_ls_dir(ls, dir) != 0)
	}
}
