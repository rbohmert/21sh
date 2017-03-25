/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crea_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 02:29:02 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/02 02:32:23 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree		*ft_crea_tree(void *content, t_tree *left, t_tree *right)
{
	t_tree *tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	else
	{
		tree->content = content;
		tree->lf = left;
		tree->rg = right;
	}
	return (tree);
}
