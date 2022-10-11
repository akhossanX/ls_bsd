/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhosssan <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:27:37 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 21:51:07 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define BUFF_SIZE	1
# define FD_MAX		4096

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef unsigned long long	t_ull;

/*
**	Conversions
*/

long long int	ft_atoll(const char *str);
char			*ft_ltoa(long long n);
char			*ft_utoa(unsigned long long n);
int				ft_atoi(const char *s);

/*
**	Memory
*/

int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memdup(const void *mem, size_t size);
void			*ft_memmove(void *dest, const void *src, size_t size);

/*
**	Strings
*/

int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isspace(int c);
int				ft_isnumeric(const char *s);

size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcasecmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strncasecmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strrep(const char *s, size_t times);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strnjoin(const char *s1, const char *s2, size_t n);
char			*ft_strjoin_free(char *s1, char *s2);
void			ft_strclr(char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *h, const char *n);
void			ft_strupper(char *str);

int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s);

int				ft_indexof(char *s, char c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_contains(const char *set, char c);

/*
**	Input Output
*/

int				ft_printf(const char *fmt, ...);
int				ft_dprintf(const int fd, const char *fmt, ...);
int				get_next_line(const int fd, char **line);
int				ft_putchar(char c);
int				ft_putstr(char const *s);
void			ft_putnchar(char c, long n);
int				ft_putchar_fd(int fd, int c);
int				ft_putnchar_fd(int fd, int c, int n);
int				ft_putstr_fd(int fd, const char *s);

/*
**	Math functions
*/

long			ft_abs(long nb);
double			ft_sqrt(int n);
int				ft_pow(int x, unsigned int y);
int				ft_round(double n);
int				nb_length(long long n);
int     		ft_ceil(double nb);

/*
**	Generic Linked List
*/

void			ft_lstdel(t_list **lst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **lst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lst_push_back(t_list **lst, t_list *new);
void			ft_lst_push_front(t_list **alst, t_list *new);


#endif
