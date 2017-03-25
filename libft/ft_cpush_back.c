/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpush_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:45:50 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 10:50:06 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cpush_back(t_clist **clist, void *content)
{
	t_clist *new;

	if (*clist)
	{
		if ((new = (t_clist *)malloc(sizeof(t_clist))))
		{
			new->content = content;
			new->next = (*clist);
			new->prev = (*clist)->prev;
			(*clist)->prev->next = new;
			(*clist)->prev = new;
		}
	}
	else
	{
		if ((*clist = (t_clist *)malloc(sizeof(t_clist))))
		{
			(*clist)->content = NULL;
			(*clist)->prev = *clist;
			(*clist)->next = *clist;
			ft_cpush_back(clist, content);
		}
	}
}
