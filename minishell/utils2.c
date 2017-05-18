/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:15:19 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 21:26:50 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"

char	**malloc_env(char **env)
{
	int		i;
	int		j;
	char	**nenv;

	i = 0;
	j = 0;
	nenv = NULL;
	while (env[i++])
		;
	if (!(nenv = (char **)malloc((i + 1) * sizeof(char *))))
		return (NULL);
	while (env[j])
	{
		nenv[j] = ft_strdup(env[j]);
		j++;
	}
	nenv[j] = NULL;
	return (nenv);
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
