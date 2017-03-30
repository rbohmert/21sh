/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 04:05:37 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/28 16:37:49 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21.h"

//possible aue del soit inutile, je crois quel delete toute la lst mais normalement y a qu'un maillon au moment ou c'est appele
void	del(t_list **lst)
{
	t_list *tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
	return ;
}

char 	**sg_env(char **env)
{
	static char **e = NULL;

	if (env != NULL)
		e = env;
	return (e);
}

char	*lsttostr(t_list *lst)
{
	char	*str;
	t_list	*l;
	int		len;

	l = lst;
	len = 0;
	while (l)
	{
		len += ft_strlen(L(l)->itm);
		l->next ? len++ : 0;
		l = l->next;
	}
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	l = lst;
	while (l)
	{
		ft_strcat(str, L(l)->itm);
		l->next ? ft_strcat(str, " ") : 0;
		l = l->next;
	}
	return (str);
}

int		ft_lstdellast(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	if(!lst->next)
		{
			close(*((int *)(lst->content)));
			free(lst);
			tmp->next = NULL;
			return (1);
		}

	while (lst->next)
	{
		lst = lst->next;
		if (!lst->next)
		{
			ft_putstr("->");
			ft_putnbr(*((int *)(lst->content)));
			close(*((int *)(lst->content)));
			free(lst);
			tmp->next = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
