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


/*char	*check(char **env, char *name, int no_built)
{
	int			i;
	char		*path;
	char		**dir;
	struct stat	buf;

	i = -1;
	if ((!no_built && check_builtins(name)) ||\
		(ft_strchr(name, '/') && !access(name, F_OK | X_OK))) 
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
}*/

char	*chrbinpath(char **env, char *name)
{
	int			i;
	char		**dir;
	struct stat buf;
	char		*path;

	i = -1;
	dir = (get_env(env, "PATH=") ? ft_strsplit(get_env(env, "PATH="), ':')\
	: NULL);
	while (dir && dir[++i] && (path = join_path(dir[i], name)))
	{
		if (!access(path, F_OK))
		{
			lstat(path, &buf);
			(buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode) ?\
			ft_tabfree(&dir) : 0;
			if ((buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode))
				return (path);
		}
		free(path);
	}
	ft_tabfree(&dir);
	return (NULL);
}

char	*check(char **env, char *name, int no_built)
{
	struct stat buf;

	if (!no_built && check_builtins(name))
		return (ft_strdup(name));
	else if (name[0] == '.' || name[0] == '/')
	{
		if (!access(name, F_OK | X_OK))
		{
			lstat(name, &buf);
			if (!S_ISDIR(buf.st_mode))
				return (ft_strdup(name));
			else
				return (NULL);
		}
	}
	return (chrbinpath(env, name));
}

/*si les fd different de ceux par default on remplace le fd par celui fournit
 et close ces fd dans le pere avec les meme condition*/
int 	exe_com(char *name, char **arg, char ***env, int fd[3], t_list *toclose)
{
	pid_t pid;

	if (name[0] != '/' && name[0] != '.')//verif passé sans path de fichier
		return (exec_builtins(name, arg, env, fd, toclose));//donc builtin
	else
	{
		pid = fork();
		if (pid < 0)
			ft_putstr("fork fail\n");
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
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
			execve(name, arg, *env);
			ft_putstr("exec fail\n");
		}
		else
		{
			free(name);
			ft_tabfree(&arg);
			if (fd[IN] != STDIN_FILENO)
				close(fd[IN]);
			if (fd[OUT] != STDOUT_FILENO)
				close(fd[OUT]);
			if (fd[ERR] != STDERR_FILENO)
				close(fd[ERR]);
			return (pid);
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
	ltab = NULL;
	if (str[0])
	{
		//ltab = ft_strsplit(str, ' ');
		ltab = make_arg(str);
		expend_arg(ltab);
		free(str);
		if (!(str = check(env, ltab[0], 0)))//check pour les builtin aussi
		{
			if (fd[IN] != STDIN_FILENO)
				close(fd[IN]);
			if (fd[OUT] != STDOUT_FILENO)
				close(fd[OUT]);
			if (fd[ERR] != STDERR_FILENO)
				close(fd[ERR]);
			ft_putstr(ltab[0]);	
			ft_putstr(": Command not found\n"); //dit ca si ./trucexistepas, a regler dans check
			ft_tabfree(&ltab);
			return (-1);
		}
		else
			return (exe_com(str, ltab, &env, fd, toclose));
	}
	free(str);
	return (-1);
}
