/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:58:31 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/10 22:57:50 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"

void	add_env(char **arg, char **env, int ac)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	if (ac == 2)
		env[i] = ft_strjoin(arg[1], "=");
	else
		env[i] = ft_strjoin(ft_strjoin(arg[1], "="), arg[2]);
	env[i + 1] = NULL;
}

void	ft_setenv(char **arg, char **env)
{
	int		ac;
	char	*str;

	ac = 0;
	while (arg[ac])
		ac++;
	if (ac == 1)
		ft_ptabstr(env);
	else if (ac > 3)
		ft_putendl("usage setenv: setnenv VAR VALUE");
	else
	{
		if (!(str = get_env(env, ft_strjoin(arg[1], "="))))
			add_env(arg, env, ac);
		else if (ac == 2)
			str[0] = 0;
		else
			ft_strcpy(str, arg[2]);
	}
}
