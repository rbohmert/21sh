/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:58:31 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 18:36:20 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"

void	add_env(char **arg, char ***env, int ac)
{
	int		i;
	char	*tmp;
	char	**nenv;

	i = 0;
	while ((*env)[i])
		i++;
	if (!(nenv = (char **)malloc((i + 2) * sizeof(char *))))
		return ;
	i = -1;
	while ((*env)[++i])
		nenv[i] = ft_strdup((*env)[i]);
	if (ac == 2)
		nenv[i] = ft_strjoin(arg[1], "=");
	else
	{
		tmp = ft_strjoin(arg[1], "=");
		nenv[i] = ft_strjoin(tmp, arg[2]);
		free(tmp);
	}
	nenv[i + 1] = NULL;
	ft_tabfree(env);
	*env = nenv;
	sg_env(*env);
}

void	change_env(char *key, char **env, char *new)
{
	int	len;
	int	i;

	len = ft_strlen(key);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, len))
		{
			free(env[i]);
			env[i] = new;
		}
	}
}

void	ft_setenv(char **arg, char ***env)
{
	int		ac;
	char	*str;
	char	*tmp;

	ac = 0;
	tmp = NULL;
	while (arg[ac])
		ac++;
	if (ac == 1)
		ft_ptabstr(*env);
	else if (ac > 3)
		ft_putendl("usage setenv: setnenv VAR VALUE");
	else
	{
		tmp = ft_strjoin(arg[1], "=");
		if (!(str = get_env(*env, tmp)))
			add_env(arg, env, ac);
		else if (ac == 2)
			str[0] = 0;
		else
			change_env(tmp, *env, ft_strjoin(tmp, arg[2]));
		free(tmp);
	}
}
