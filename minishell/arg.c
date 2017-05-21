/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:55:20 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 20:42:09 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"

int		cnt_arg(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
			if (*str == '"' || *str == '\'')
				str = ft_strchr(str + 1, *str) + 1;
		else if (*str != ' ')
			str++;
		else
		{
			str++;
			i++;
		}
	}
	return (++i);
}

int		len_arg(char *str)
{
	int		len;
	char	*sav2ndcote;

	len = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			sav2ndcote = ft_strchr(str + 1, *str);
			len += sav2ndcote - str + 1;
			str = sav2ndcote + 1;
		}
		else if (*str != ' ')
		{
			len++;
			str++;
		}
		else
			return (len);
	}
	return (len);
}

char	**make_arg(char *str)
{
	char	**arg;
	int		i;
	int		nb;
	int		len;

	nb = cnt_arg(str);
	i = 0;
	if (!(arg = (char **)malloc((nb + 1) * sizeof(char *))))
		return (NULL);
	arg[nb] = NULL;
	while (i < nb)
	{
		len = len_arg(str);
		arg[i] = ft_strndup(str, len);
		str = str + len + 1;
		i++;
	}
	return (arg);
}
