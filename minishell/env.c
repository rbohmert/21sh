/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 22:02:48 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/11 01:37:35 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cp_env(char **env)
{
	int		i;
	char	**nenv;

	i = 0;
	while (env[i])
		i++;
	nenv = (char **)malloc((i + 10) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		nenv[i] = env[i];
		i++;
	}
	nenv[i] = NULL;
	return (nenv);
}

void	clr_env(char **nenv)
{
	int i;

	i = 0;
	while (nenv[i])
	{
		i++;
		nenv[i - 1] = NULL;
	}
}

void	add_key(char *str, char **nenv)
{
	int i;

	i = 0;
	while (nenv[i])
		i++;
	nenv[i] = ft_strdup(str);
	nenv[i + 1] = NULL;
}

void	env_opt(char **arg, char **nenv, int *i)
{
	while (arg[*i] && arg[*i][0] == '-')
	{
		if (arg[*i][1] == 'i' && arg[*i][2] == 0)
			clr_env(nenv);
		else if (arg[*i][1] == 'u' && arg[*i][2] == 0 && arg[*i + 1])
			ft_unsetenv(arg + (*i)++, nenv);
		else
			ft_putstr("usage env [-i] [-u name] [utility [arguments ...]]\n");
		(*i)++;
	}
	while (arg[*i] && ft_strchr(arg[*i], '='))
		add_key(arg[(*i)++], nenv);
}

void	ft_env(char **arg, char **env)
{
	int		i;
	char	**nenv;
	char	*com;

	i = 1;
	nenv = cp_env(env);
	env_opt(arg, nenv, &i);
	if (arg[i] && (com = check(env, arg[i], 1)))
		exe_com(com, arg + i, nenv, NULL, NULL);
	else if (!arg[i])
		ft_ptabstr(nenv);
	else
	{
		ft_putstr("env: ");
		ft_putstr(arg[i]);
		ft_putstr(": commande introuvable\n");
	}
	free(nenv);
}
