/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 22:39:24 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/11 01:37:41 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtins(char *name, char **arg, char **env)
{
	if (!(ft_strcmp(name, "cd")))
		cd(arg, env);
	if (!(ft_strcmp(name, "echo")))
		echo(arg);
	if (!(ft_strcmp(name, "env")))
		ft_env(arg, env);
	if (!(ft_strcmp(name, "setenv")))
		ft_setenv(arg, env);
	if (!(ft_strcmp(name, "unsetenv")))
		ft_unsetenv(arg, env);
	if (!(ft_strcmp(name, "exit")))
		exit(2);
	return(0);//a changer pour retour builtin (tjr ok pour le moment)
}

void	ft_chdir(char *target, char *oldpwd, char **env)
{
	char buf[200];

	if (!chdir(target))
	{
		getcwd(buf, 200);
		if (get_env(env, "OLDPWD="))
			ft_strcpy(get_env(env, "OLDPWD="), oldpwd);
		if (get_env(env, "PWD="))
			ft_strcpy(get_env(env, "PWD="), buf);
	}
	else
		ft_putstr("File not exist or no access right\n");
}

void	cd(char **arg, char **env)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
		ft_putstr("Too many arguments\n");
	else
	{
		if (arg[1] == NULL)
			ft_chdir(get_env(env, "HOME="), get_env(env, "PWD="), env);
		else if (arg[1][0] == '-')
			ft_chdir(get_env(env, "OLDPWD="), get_env(env, "PWD="), env);
		else
			ft_chdir(arg[1], get_env(env, "PWD="), env);
	}
}

void	ft_unsetenv(char **arg, char **env)
{
	int ac;
	int i;

	ac = 0;
	i = 0;
	while (arg[ac])
		ac++;
	if (ac == 1)
		ft_ptabstr(env);
	if (ac == 2 || !ft_strcmp(arg[0], "-u"))
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], arg[1], ft_strlen(arg[1])))
			{
				env[i] = NULL;
				while (env[++i])
					env[i - 1] = env[i];
				env[i - 1] = NULL;
			}
			i++;
		}
	}
}

void	echo(char **arg)
{
	arg++;
	while (*arg)
	{
		ft_putstr(*arg);
		(*(arg + 1)) ? ft_putchar(' ') : ft_putchar('\n');
		arg++;
	}
}
