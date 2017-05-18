/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrandria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:58:11 by nrandria          #+#    #+#             */
/*   Updated: 2017/03/26 16:36:12 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_tree
{
	void			*content;
	struct s_tree	*rg;
	struct s_tree	*lf;
}					t_tree;

typedef struct		s_clist
{
	void			*content;
	struct s_clist	*next;
	struct s_clist	*prev;
}					t_clist;

typedef struct		s_2list
{
	void			*content;
	struct s_2list	*next;
	struct s_2list  *prev;
}					t_2list;

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isprint(int c);
int					ft_atoi(const char *str);
int					ft_strcmp(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putstr(char const *str);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strequ(char const *s1, char const *s2);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f) (char *));
void				ft_striteri(char *s, void (*f) (unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_putnbr_fd(int n, int fd);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *nw);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_lstlen(t_list *beg);
void				ft_cpushback(t_clist *clist, void *content);
t_list				*ft_create_elem(void *content, size_t content_size);
void				ft_push_back(t_list **list, void *content,
					size_t content_size);
void				ft_push_front(t_list **list, void *content,
					size_t content_size);
t_list				*ft_lstat(t_list **list, unsigned int n);
void				ft_ptabstr(char **str);
t_list				*ft_lstcut(t_list *end_first_lst);
t_tree				*ft_crea_tree(void *content, t_tree *let, t_tree *right);
void				ft_lstcat(t_list *lst1, t_list *lst2);
char				*ft_strndup(char *str, int n);
t_2list				*ft_create_2lst(void *content);
void				ft_push_2back(t_2list **lst, void *content);
void				ft_push_2front(t_2list **lst, void *content);
void				ft_freestrtab(char **strtab);
char				**ft_tabdup(char **tab);
#endif
