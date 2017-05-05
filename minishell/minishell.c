/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 19:09:49 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/31 10:56:07 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21.h"


char	*check(char **env, char *name, int no_built)
{
	int			i;
	char		*path;
	char		**dir;
	struct stat	buf;

	i = -1;
	if ((!no_built && check_builtins(name)) ||\
		(ft_strchr(name, '/') && !access(name, F_OK))) 
		return (ft_strdup(name));
	if (get_env(env, "PATH="))
		dir = ft_strsplit(get_env(env, "PATH="), ':');
	else
		dir = NULL;
	while (dir && dir[++i])
	{
		path = join_path(dir[i], name);
		if (!access(path, F_OK))
		{
			lstat(path, &buf);
			if ((buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode))
			{
				ft_freestrtab(dir);
				return (path);
			}
		}
		free(path);
	}
	ft_freestrtab(dir);
	return (NULL);
}

/*si les fd different de ceux par default on remplace le fd par celui fournit
 et close ces fd dans le pere avec les meme condition*/
int 	exe_com(char *name, char **arg, char **env, int fd[3], t_list *toclose)
{
	pid_t pid;

	if (name[0] != '/' && name[0] != '.')//verif passé sans path de fichier
		return (exec_builtins(name, arg, env));//donc builtin
	else
	{
		pid = fork();
		if (pid < 0)
			ft_putstr("fork fail\n");
		else if (pid == 0)
		{
			multiclose(toclose);
			if (fd[IN] != STDIN_FILENO)
			{
				dup2(fd[IN], STDIN_FILENO);
				close(fd[IN]);
			}
			if (fd[OUT] != STDOUT_FILENO)
			{
				dup2(fd[OUT], STDOUT_FILENO);
				close(fd[OUT]);
			}
			if (fd[ERR] != STDERR_FILENO)
			{
				dup2(fd[ERR], STDERR_FILENO);
				close(fd[ERR]);
			}
			execve(name, arg, env);
			ft_putstr("exec fail\n");
		}
		else
		{
			free(name);
			ft_freestrtab(arg);
			if (fd[IN] != STDIN_FILENO)
				close(fd[IN]);
			if (fd[OUT] != STDOUT_FILENO)
				close(fd[OUT]);
			if (fd[ERR] != STDERR_FILENO)
				close(fd[ERR]);
			return (1);
		}
	}
	return(1);
}

//verifie la ligne de commande doit y avoir un pb avec les builins
int 	verif_line(char *str, int fd[3], t_list *toclose)
{
	char **ltab;
	char **env; //changer toute cette merde de env qui passe partout sg_env(NULL)

	env = sg_env(NULL);
	if (str[0])
	{
		ltab = ft_strsplit(str, ' ');
		free(str);
		if (!(str = check(env, ltab[0], 0)))//check pour les builtin aussi
		{
			ft_freestrtab(ltab);
			ft_putstr("Command not found\n"); //dit ca si ./trucexistepas, a regler dans check
			return (-1);
		}
		else
			return (exe_com(str, ltab, env, fd, toclose));
	}
	return (-1);
}
