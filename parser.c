/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 13:34:16 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/11 05:52:37 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21.h"

void 	error_parse()
{
	ft_putstr("error parse");
	getchar();
	exit(2);
}

//cherche maillon fin de la premiere liste (on va couper lst en 2)
//1e maillon PIPE ou SEP erreur
//cas spe RED au 1e maillon -> renvoie 2eme maillon
//pour les SEP cherche en 1e ';', puis reste, par la fin
//pour les autre dans l'ordre de la liste
t_list	*lstchrend(t_list *lst, int flag)
{
	t_list *tmp;

	tmp = NULL;
	if ((L(lst)->type & PIP) || (L(lst)->type & SEP))
		error_parse();
	if (flag == RED && L(lst)->type & RED)
		return (lst->next);
	while (lst->next)
	{
		if ((flag == PIP || flag == RED) && (L(lst->next)->type & flag) > 0)
			return (lst);
		else if (flag == SEP && (L(lst->next)->type & flag) > 0)
		{
			if (!ft_strcmp(L(lst->next)->itm, ";"))
				return (lst);
			else
				tmp = lst;
		}
		lst = lst->next;
	}
	return (tmp);
}

t_tree	*make_tree(t_list *beg, t_list *end, int flag)
{
	t_tree *tree;

	tree = NULL;
	if (flag == SEP || flag == PIP)
	{
		end = ft_lstcut(end);
		tree = ft_crea_tree(end->content, parser(beg), parser(end->next));
		free(end);
	}
	else if (flag == RED)
	{
		if (ISRED(L(beg)->type))//comm au dessus
		{
			if ((!end || ISSYM(L(end)->type)) && !ISRFD(L(beg)->type))
				error_parse();
			else if (ISRFD(L(beg)->type))
			{
				tree = ft_crea_tree(beg->content, NULL, parser(end));
				free(beg);
			}
			else
			{
				tree = ft_crea_tree(beg->content, ft_crea_tree(end, NULL, NULL), parser(end->next));
				free(beg);
			}
		}
		else
		{
			end =  ft_lstcut(end);
			if ((!(end->next) || ISSYM(L(end->next)->type)) && !ISRFD(L(end)->type))
				error_parse();
			else if (ISRFD(L(end)->type))
			{
				ft_lstcat(beg, end->next);
				tree = ft_crea_tree(end->content, NULL, parser(beg));
			}
			else
			{
				ft_lstcat(beg, end->next->next);
				ft_lstcut(end->next);
				tree = ft_crea_tree(end->content, ft_crea_tree(end->next, NULL, NULL), parser(beg));
			}
			free(end);
		}
	}
	return (tree);
}//met des liste dans content du tree... peux beug, certainement dans cas RED debut ligne (aux comm au dessus)

t_tree	*parser(t_list *beg)
{
	t_list *lst;
	t_tree *tree;

	if (beg == NULL)
		return (NULL);
	else if ((lst = lstchrend(beg, SEP)))
		tree = make_tree(beg, lst, SEP);
	else if((lst = lstchrend(beg, PIP)))
		tree = make_tree(beg, lst, PIP);
	else if((lst = lstchrend(beg, RED)))
		tree = make_tree(beg, lst, RED);
	else
		tree = ft_crea_tree(beg, NULL, NULL);
	return (tree);
}
