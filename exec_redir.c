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

#include "includes/21.h"

char *addretline(char *str)
{
	char *new;

	new = ft_strnew(ft_strlen(str + 2));
	ft_strcpy(new, str);
	ft_strcat(new, "\n");
	free(str);
	return(new);
}

//attend sur l'entree standard jusqu'au endword, envois tout ce qui est ecrit dans le pipe
int heredoc(char *endword, t_list *toclose)
{
	int pid;
	int pip[2];
	char *line;

	pipe(pip);
	if ((pid = fork()) < 0)
		ft_putstr("la vieille forkette");
	else if (pid == 0)
	{
		multiclose(toclose);
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
//attend sur la lecture du pipe et ecrit dans un fichier,renvois le bout pour ecrire
int	redir_outfile(char *name, int flag, t_list *toclose)
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
		multiclose(toclose);
		close(pip[1]);
		fdfile = open(name, O_WRONLY | O_CREAT | (flag ? O_APPEND : O_TRUNC), 0644);
		while (read(pip[0], buf, 1))
			write(fdfile ,buf, 1);
		exit(0);
	}
	close(pip[0]);
	return (pip[1]);
}

//lis le fichier name et envois dans le pipe
int redir_infile(char *name, t_list *toclose)
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
		multiclose(toclose);
		close(pip[0]);
		fdfile = open(name, O_RDONLY);
		while (read(fdfile, buf, 1))
			write(pip[1], buf, 1);
		exit(0);
	}
	close(pip[1]);
	return (pip[0]);
}

//fais les agregation, efface list de sortie pour la remplacer par l'autre
void	res_aggreg(t_tree *tree, t_list *fd[4])
{
	//ft_putnbr(((char *)T(tree)->itm)[0] - 48);
	if (((char *)T(tree)->itm)[0] == ((char *)T(tree)->itm)[3])
		return ;
	del_close_lst(&fd[((char *)T(tree)->itm)[0] - 48], 1);
	fd[((char *)T(tree)->itm)[0] - 48] = fd[((char *)T(tree)->itm)[3] - 48];
	res(tree->rg, fd);
	
}

/*en gros, si pas une aggregation (&), recupere un fd suivant la fonction de 
redirection et le push dans la liste corespondante, et res a droite puis 
close et del de la list le fd qui sert plus a rien une fois le res finit
le noeud de gauche contient le nom du fichier ou endword pour les redir*/
int exec_redirection(t_tree *tree, t_list *fd[4])
{
	int		fdpip;

	if (((char *)T(tree)->itm)[2] != '&') 
	{
		if (((char *)T(tree)->itm)[1] == '>')
		{
			if (((char *)T(tree)->itm)[2] == '>')
				fdpip = redir_outfile(lsttostr(tree->lf->content), 1, fd[TOCLOSE]);
			else
				fdpip = redir_outfile(lsttostr(tree->lf->content), 0, fd[TOCLOSE]);
			ft_push_back(&fd[((char *)T(tree)->itm)[0] - 48], NULL, fdpip);
			res(tree->rg, fd);
			close(fdpip);
			fd[((char *)T(tree)->itm)[0] - 48] = ft_lstdellast(fd[((char *)T(tree)->itm)[0] - 48], 1);// char - 48 ->trick pour atoi avec un char
		}
		else if (((char *)T(tree)->itm)[0] == '<')
		{
			if (((char *)T(tree)->itm)[1] == '<')
				fdpip = heredoc(lsttostr(tree->lf->content), fd[TOCLOSE]);
			else 
				fdpip = redir_infile(lsttostr(tree->lf->content), fd[TOCLOSE]);
			ft_push_back(&fd[IN], NULL, fdpip);
			res(tree->rg, fd);
			fd[IN] = ft_lstdellast(fd[IN], 1);
		}
	}
	else
		res_aggreg(tree, fd);
	return (1);
}
