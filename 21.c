/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:12:56 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/31 11:00:32 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/21.h"
//debug
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

//debug
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

//normalement inutile, getlinetcap doit pas prendre non ascii
int isimprchar(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ISCHARIMP(*str))
			return (0);
		str++;
		return (1);
	}
	return (1);
}

void	free_tree(t_tree *tree)
{
	t_list *lst;
	t_list *tmp;

	if (!tree)
		return;
	if (tree->rg || tree->lf)
	{
		free_tree(tree->rg);
		free_tree(tree->lf);
		free(T(tree)->itm);
		free(tree->content);
		free(tree);
	}
	else
	{
		lst = tree->content;
		while (lst)
		{
			tmp = lst;
			lst = lst->next;
			free(L(tmp)->itm);
			free(tmp->content);
			free(tmp);
		}
		free(tree);
	}
}
	
int main(int ac , char **av, char **env)
{
	char *line;
	t_list *lst;
	t_list *tablist[4];
	t_tree *tre;

	ac = ac;
	av =av;
	sg_env(env); // save env dans une static
	bzero(tablist, sizeof(t_list *) * 4);
	block_sig();
	ft_putstr("?>");
	line = NULL;
	while ((line = get_line_tcap()))
	{
		if (isimprchar(line))
		{
			//ft_putendl(line);
			strtrim(&line);
			lst = lexer(line);
			//ft_putlist(lst);
			tre = parser(lst);
			//ptree(tre);
			res(tre, tablist);
			free_tree(tre);
			bzero(tablist, sizeof(t_list *) * 4);
			while (wait(0) > 0)//attend tous les fils
				;
		}
		else
			ft_putstr("non char");
		free(line);
		ft_putstr("?>");
	}
	return (0);
}
