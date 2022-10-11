
#include "ft_ls.h"

/*
**  Bonus
**  Dispaly the directory entries in block format
*/

void    get_cols_rows(int max, int nentries, int *cols, int *rows)
{
    *cols = 1;
    *rows = 1;
    while (*cols * *rows < nentries && *cols < max)
    {
        (*rows)++;
        *cols = ft_ceil((double)nentries / *rows);
        while (*cols > max)
        {
            (*rows)++;
            *cols = ft_ceil((double)nentries / *rows);
        }
    } 
}

char    ***new_block_array(t_ls *ls, int rows, int cols)
{
    char    ***arr;
    int     i;

    errno = 0;
    if (!(arr = (char ***)ft_memalloc(sizeof(char **) * rows)))
    {
        ls->err = errno;
        ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
    }
    i = 0;
    while (i < rows)
    {
        if (!(arr[i] = (char **)ft_memalloc(sizeof(char *) * cols)))
        {
            ls->err = errno;
            ls_handle_error(ls, NULL, LS_MAJOR_ERROR);
        }
        i++;
    }
    return (arr);
}

void    fill_block_array(t_path *lst, char ***arr, int rows, int cols)
{
    int i;
    int j;

    i = 0;
    while (lst && i < cols)
    {
        j = 0;
        while (lst && j < rows)
        {
            arr[j][i] = lst->name;
            j++;
            lst = lst->next;
        }
        i++;
    }
}

void    disp_in_blocks(t_ls *ls, t_path *lst, int rows, int cols, int width)
{
    char  ***arr;
    int   i;
    int   j;

    arr = new_block_array(ls, rows, cols);
    fill_block_array(lst, arr, rows, cols);
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols && arr[i][j] != NULL)
        {
            ft_printf("%-*s", width, arr[i][j]);
            write(1, j == cols - 1 ? "" : " ", 1);
            j++;
        }
        write(1, "\n", 1);
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    disp_one_line(t_path *lst, int width)
{
    while (lst)
    {
        ft_printf("%-*s", width, lst->name);
        lst = lst->next;
        ft_printf(lst ? " " : "\n");
    }
}


void    block_display(t_ls *ls, t_path *lst, int dir_or_files)
{
    int     max;
    int     maxlength;
    int     entries;
    int     cols;
    int     rows;

    maxlength = (dir_or_files == DIRECTORY) ? ls->display.max_dirs_names :
        ls->display.max_files_names;
    entries = (dir_or_files == DIRECTORY) ? ls->display.total_dirs :
        ls->display.total_files;
    max = ls->display.wincolumns / (maxlength + 1);
    if (entries <= max)
        disp_one_line(lst, maxlength);
    else
    {
        get_cols_rows(max, entries, &cols, &rows);
        disp_in_blocks(ls, lst, rows, cols, maxlength);
    }
}

