/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 18:59:56 by rbohmert          #+#    #+#             */
/*   Updated: 2016/12/03 21:05:44 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strtrim(char **str)
{
	char *tmp;
	char *nstr;
	char *nstrtmp;

	tmp = *str;
	nstr = ft_strnew(ft_strlen(tmp));
	nstrtmp = nstr;
	while (*tmp == '\t' || *tmp == '\v' || *tmp == ' ')
		tmp++;
	while (*tmp)
	{
		if (*tmp != '\t' && *tmp != '\v' && *tmp != ' ')
			*(nstr++) = *tmp;
		else if (*(tmp + 1) && (*(tmp + 1) != '\t' &&\
				*(tmp + 1) != '\v' && *(tmp + 1) != ' '))
			*(nstr++) = ' ';
		tmp++;
	}
	*nstr = 0;
	free(*str);
	*str = nstrtmp;
}

int		check_builtins(char *name)
{
	char	*builtins[7];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "env";
	builtins[3] = "setenv";
	builtins[4] = "unsetenv";
	builtins[5] = "exit";
	builtins[6] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (name && !(ft_strcmp(name, builtins[i])))
			return (1);
		i++;
	}
	return (0);
}

char	*get_env(char **env, char *key)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(key);
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, len) == 0)
			return (env[i] + len);
	}
	return (NULL);
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
