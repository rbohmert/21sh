/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:27:38 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/31 11:05:41 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21.h"

char *addretline(char *str)
{
	char *new;

	new = ft_strnew(ft_strlen(str + 2));
	ft_strcpy(new, str);
	ft_strcat(new, "\n");
	free(str);
	return(new);
}

	

int heredoc(char *endword)
{
	int pid;
	int pip[2];
	char *line;

	pipe(pip);
	if ((pid = fork()) < 0)
		ft_putstr("la vieille forkette");
	else if (pid == 0)
	{
		close(pip[0]);
		ft_putstr("heredoc>");
		while (get_next_line(0, &line))
		{
			if (!ft_strcmp(line, endword))
				break;
			line = addretline(line);
			ft_putstr_fd(line, pip[1]);
			free(line);
			ft_putstr("heredoc>");
		}
		exit(0);
	}
	waitpid(pid, 0, 0);
	close(pip[1]);
	return (pip[0]);
}

int	redir_outfile(char *name, int flag)
{
	int pid;
	int pip[2];
	int fdfile;
	char buf[2];

	pipe(pip);
	if ((pid = fork()) < 0)
		ft_putstr("c'est la merde frero");
	else if (pid == 0)
	{
		close(pip[1]);
		fdfile = open(name, O_WRONLY | O_CREAT | (flag ? O_APPEND : O_TRUNC), 0644);
		while (read(pip[0], buf, 1))
			write(fdfile ,buf, 1);
		exit(0);
	}
	close(pip[0]);
	return (pip[1]);
}

int redir_infile(char *name)
{
	int pid;
	int pip[2];
	int fdfile;
	char buf[2];

	pipe(pip);
	if ((pid = fork()) < 0)
		ft_putstr("fork moisi");
	else if (pid == 0)
	{
		close(pip[0]);
		fdfile = open(name, O_RDONLY);
		while (read(fdfile, buf, 1))
			write(pip[1], buf, 1);
		exit(0);
	}
	close(pip[1]);
	return (pip[0]);
}

int exec_redirection(t_tree *tree, t_list *in, t_list *out)
{
	t_list *tmp;
	int		fd;

	tmp = out;
	if (((char *)T(tree)->itm)[2] != '&') 
	{
		if (((char *)T(tree)->itm)[1] == '>')
		{
			if (((char *)T(tree)->itm)[2] == '>')
				fd = redir_outfile(lsttostr(tree->lf->content), 1);
			else
				fd = redir_outfile(lsttostr(tree->lf->content), 0);
			ft_push_back(&out, &fd, 0);
			res(tree->rg, in, out);
			close(fd);
			ft_lstdellast(out);
		}
		else if (((char *)T(tree)->itm)[0] == '<')
		{
			if (((char *)T(tree)->itm)[1] == '<')
				fd = heredoc(lsttostr(tree->lf->content));
			else 
				fd = redir_infile(lsttostr(tree->lf->content));
			ft_push_back(&in, &fd, 0);
			res(tree->rg, in, out);
			ft_lstdellast(in);
		}
	}
	return (1);
}


