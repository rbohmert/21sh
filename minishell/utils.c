/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 18:59:56 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 21:27:24 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"

void	ft_tabfree(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		((*arr)[i]) != NULL ? free((*arr)[i]) : 0;
		(*arr)[i] = NULL;
		i++;
	}
	((*arr)[i]) != NULL ? free((*arr)[i]) : 0;
	(*arr)[i] = NULL;
	*arr != NULL ? free(*arr) : 0;
	*arr = NULL;
}

void	stn2(char *str, char *tmp)
{
	char *sav2ndcote;

	while (*tmp)
	{
		if (*tmp == '"' || *tmp == '\'')
		{
			sav2ndcote = ft_strchr(tmp + 1, *tmp);
			ft_strncpy(str, tmp, sav2ndcote - tmp + 1);
			str += sav2ndcote - tmp + 1;
			tmp = sav2ndcote;
		}
		else if (*tmp != '\t' && *tmp != '\v' && *tmp != ' ')
			*(str++) = *tmp;
		else if (*(tmp + 1) && (*(tmp + 1) != '\t' &&\
				*(tmp + 1) != '\v' && *(tmp + 1) != ' '))
			*(str++) = ' ';
		tmp++;
	}
	*str = 0;
}

void	strtrim_nocote(char **str)
{
	char *tmp;
	char *nstr;

	tmp = *str;
	nstr = ft_strnew(ft_strlen(tmp) + 1);
	while (*tmp == '\t' || *tmp == '\v' || *tmp == ' ')
		tmp++;
	stn2(nstr, tmp);
	free(*str);
	*str = nstr;
}

int		check_builtins(char *name)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "env";
	builtins[3] = "setenv";
	builtins[4] = "unsetenv";
	builtins[5] = "exit";
	builtins[6] = "history";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (name && !(ft_strcmp(name, builtins[i])))
			return (1);
		i++;
	}
	return (0);
}

char	*join_path(char *s1, char *s2)
{
	char *s;

	s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	ft_strcpy(s, s1);
	ft_strcat(s, "/");
	ft_strcat(s, s2);
	return (s);
}
