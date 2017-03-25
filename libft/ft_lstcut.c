/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 02:21:24 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/02 02:38:36 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstcut(t_list *end_first_lst)
{
	t_list *beg_new_lst;

	beg_new_lst = end_first_lst->next;
	end_first_lst->next = NULL;
	return (beg_new_lst);
}
