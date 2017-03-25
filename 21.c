/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:12:56 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/25 05:31:38 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21.h"

void	ft_putlist(t_list *lst)
{
	ft_putendl("-------------------------------");
	ft_putendl(lsttostr(lst));
	while (lst)
	{
		ft_putstr(L(lst)->itm);
		ft_putchar('\t');
		ft_putchar('\t');
		ft_putchar('\t');
		ft_putnbr(L(lst)->type);
		ft_putchar('\n');
		lst = lst->next;
	}
	ft_putendl("-------------------------------");
}

void	ptree(t_tree *tre)
{
	if (tre == NULL)
	{
		ft_putstr("rieeeeeeeeeeeeeeen");
		return ;
	}
	if (T(tre)->type == 0)
		ft_putlist(tre->content);
	else
	{
		ft_putstr("noeud= ");
		ft_putendl(T(tre)->itm);
	}
	if (tre->lf)
	{
		ft_putstr("l= ");
		ptree(tre->lf);
	}
	if (tre->rg)
	{
		ft_putstr("r= ");
		ptree(tre->rg);
	}
}


int main(int ac , char **av, char **env)
{
	char *line;
	t_list *lst;
	t_tree *tre;

	ft_putstr("?>");
	sg_env(env);
	line = NULL;
	while (get_next_line(0, &line))// && line)
	{
		lst = lexer(ft_strtrim(line));
	//	ft_putlist(lst);
		tre = parser(lst);
	//	ptree(tre);
		res(tre, NULL, NULL);
		ft_putstr("?>");
	}
}
