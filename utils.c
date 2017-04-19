/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 04:05:37 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/31 10:55:31 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/21.h"

//close tout les fd de la liste
void	multiclose(t_list *toclose)
{
	while (toclose)
	{
		close(toclose->content_size);
		toclose = toclose->next;
	}
}

//delete et close (ou pas) la list
void	del_close_lst(t_list **lst, int flag)
{
	t_list *tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		flag ? close(tmp->content_size) : 0;
		free(tmp);
	}
	*lst = NULL;
	return ;
}
//env stocké dans une static
char 	**sg_env(char **env)
{
	static char **e = NULL;

	if (env != NULL)
		e = env;
	return (e);
}
//liste to str avec les liste d'item, en colant les mot avec des ' ' entre chaque
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
	str = ft_strnew(len + 1);
	l = lst;
	while (l)
	{
		ft_strcat(str, L(l)->itm);
		l->next ? ft_strcat(str, " ") : 0;
		l = l->next;
	}
	return (str);
}
//delete et close (ou pas) le dernier maillon de la liste
t_list		*ft_lstdellast(t_list *lst, int flag)
{
	t_list *tmp;
	t_list *start;

	start = lst;
	tmp = lst;
	if(!lst->next)
	{
		flag ? close(lst->content_size) : 0;
		free(lst);
		tmp->next = NULL;
		return (NULL);
	}
	while (lst->next)
	{
		lst = lst->next;
		if (!lst->next)
		{
			flag ? close(lst->content_size) : 0;
			free(lst);
			tmp->next = NULL;
			return (start);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
