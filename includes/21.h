/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 04:33:53 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/29 17:31:25 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEUXUN_H
# define DEUXUN_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "minishell.h"
# include "line_edit.h"
# include "history.h"
# include "autocomplete.h"
# define SYM 0b00000001
# define SEP 0b00000010
# define PIP 0b00000100
# define RED 0b00001000
# define RFD 0b00010000
# define CISSYM(c) (c == '<' || c == '>' || c == ';' || c == '|' || c == '&')
# define TYPE content_size
# define ISCHARIMP(c) (c > 31 && c < 127) 
# define ISSYM(x) (x & SYM)
# define ISSEP(x) (x & SEP)
# define ISPIP(x) (x & PIP)
# define ISRED(x) (x & RED)
# define ISRFD(x) (x & RFD)
# define L(x) ((t_item *)(x->content))
# define T(x) ((t_item *)(x->content))
# define IN 0
# define OUT 1
# define ERR 2
# define TOCLOSE 3


typedef	struct	s_item
{
	void		*itm;
	int			type;
}				t_item;

t_list	*lexer(char *line);
t_tree	*parser(t_list *beg);
t_tree	*make_tree(t_list *beg, t_list *end, int flag);
t_list	*lstchrend(t_list *lst, int flag);
int		res(t_tree *tree, t_list *fd[4]);
char 	*lsttostr(t_list *lst);
char	**sg_env(char **env);
int		manage_in(t_list *in, t_list *toclose);
int		manage_out(int outcom, t_list *out, t_list *toclose);
char	*lsttostr(t_list *lst);
t_list	*ft_lstdellast(t_list *lst, int flag);
void	del_close_lst(t_list **lst, int flag);
char	**sg_env(char **env);
int		exec_redirection(t_tree *tree, t_list *fd[4]);
void	multiclose(t_list *toclose);

#endif
