/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 22:39:24 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 21:23:27 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"

int		exec_builtins(char *name, char **arg, char ***env)
{
	if (!(ft_strcmp(name, "cd")))
		cd(arg, *env);
	if (!(ft_strcmp(name, "echo")))
		echo(arg);
	if (!(ft_strcmp(name, "env")))
		ft_env(arg, *env);
	if (!(ft_strcmp(name, "setenv")))
		ft_setenv(arg, env);
	if (!(ft_strcmp(name, "unsetenv")))
		ft_unsetenv(arg, *env);
	if (!(ft_strcmp(name, "exit")))
	{
		free(name);
		ft_tabfree(&arg);
		ft_tabfree(env);
		exit(0);
	}
	ft_tabfree(&arg);
	free(name);
	return (0);
}


void	ft_chdir(char *target, char *oldpwd, char **env)
{
	char buf[200];

	ft_bzero(buf, 200);
	if (!chdir(target))
	{
		getcwd(buf, 200);
		if (get_env(env, "OLDPWD="))
			change_env("OLDPWD=", env, ft_strjoin("OLDPWD=", oldpwd));
		if (get_env(env, "PWD="))
			change_env("PWD=", env, ft_strjoin("PWD=", buf));
	}
	else
		ft_putstr_fd("File not exist or no access right\n", 2);
}

void	cd(char **arg, char **env)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
		ft_putstr_fd("Too many arguments\n", 2);
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
	i = -1;
	while (arg[ac])
		ac++;
	if (ac == 1)
		ft_ptabstr(env);
	if (ac == 2 || !ft_strcmp(arg[0], "-u"))
	{
		while (env[++i])
		{
			if (!ft_strncmp(env[i], arg[1], ft_strlen(arg[1])))
			{
				free(env[i]);
				env[i] = NULL;
				while (env[++i])
					env[i - 1] = env[i];
				env[i - 1] = NULL;
				break ;
			}
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
