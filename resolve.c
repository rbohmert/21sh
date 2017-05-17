/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 03:39:22 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/31 10:58:36 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/21.h"

/*faut que je finisse ca, lance res sur gauche puis droite, selon le separateur;
pour savoir si le res s'est bien fini on doit recuperer avec wait donc ret inutile,
pas fais*/
int		exec_separation(t_tree *tree, t_list *fd[4])
{
	int ret;
	int status;

	ret = 1;
	if (!ft_strcmp(T(tree)->itm, ";"))
	{
		res(tree->lf, fd);
		while (wait(&ret) > 0)
			;
		res(tree->rg, fd);
	}
	if (!ft_strcmp(T(tree)->itm, "&&"))
	{
		res(tree->lf, fd);
		while (wait(&status) > 0)
		{
			ret = WIFEXITED(status) == 1 ? ret : 0;
			ret = WEXITSTATUS(status) == 0 ? ret : 0;
		}
		ret ? res(tree->rg, fd) : 0;
	}
	if (!ft_strcmp(T(tree)->itm, "||"))
	{
		res(tree->lf, fd);
		while (wait(&status) > 0)
		{
			ret = WIFEXITED(status) == 1 ? ret : 0;
			ret = WEXITSTATUS(status) == 0 ? ret : 0;
		}
		ret ? 0 : res(tree->rg, fd);
	}
	if (!ft_strcmp(T(tree)->itm, "&"))
	{
		ft_putendl("CEEEEEEEEEEEEECIIIIIIIIIII EEEESSSTTT EEEENNN BBBAACCCKKKGGRRROOOOOUUUUNNNDDDD");
		if (res(tree->lf, fd))
			ret = res(tree->rg, fd);
	}
	return (ret);	
}

/*fais un pipe, donne le bout lecture a droite et le bout ecriture a gauche
fd[TOCLOSE]c'est tout les fd a fermer a chaque fois qu'on fork(faut pas que le bout
d'ecriture reste ouvert dans un fils*/
int exec_pipe(t_tree *tree, t_list *fd[4])
{	
	int		pip[2];
	int 	ret;
	t_list	*tmp;

	ret = 0;
	if (pipe(pip) == -1)
		ft_putstr("pipeeerrroror");
	tmp = fd[IN];//retient les in pour les envoyer a gauche apres
	fd[IN] = NULL;
	ft_push_back(&fd[IN], NULL, pip[0]);//met donc le bout le lecture dans in
	ft_push_back(&fd[TOCLOSE], NULL, pip[1]);//et ecriture a fermer pour le moment
	ret = res(tree->rg, fd);//envois tout ca a droite
	fd[TOCLOSE] = ft_lstdellast(&(fd[TOCLOSE]), 0);//maintenant enleve ecriture des fd a fermer
	close(pip[0]);//ferme lecture
	del_close_lst(&fd[IN], 0);//delete la liste in qui etait pour la droite
	fd[IN] = tmp; //remet les in
	ft_push_back(&fd[OUT], NULL, pip[1]);//met le bout ecriture dans out 
	ret = res(tree->lf, fd); //envois a gauche
	fd[OUT] = ft_lstdellast(&(fd[OUT]), 0);
	close(pip[1]);//ferme ecriture
	return (ret);
}

/*gere l'xecution de la commande et les managers in et out, creer un tab de 3fd
in out err, et pipe suivant les besoin*/
int		exec_command(t_tree *tree, t_list *fd_lst[4])
{
	int fd[3];
	int pipout[2];
	int piperr[2];
	int ret;
	
	fd[IN] = IN;
	fd [OUT] = OUT;
	fd [ERR] = ERR;//par defaut in = 0 out =1 err= 2
	/*recupere le bout lecture du manage in pour fd[in]
	  et le bout  ecriture pour manage in et err
		si les liste concerné existe a chaque fois*/
	if (fd_lst[IN])
		fd[IN] = manage_in(fd_lst[IN], fd_lst[TOCLOSE]);
	if (fd_lst[OUT])
	{
		pipe(pipout);
		fd[OUT] = pipout[1];
	}	
	if (fd_lst[ERR])
	{
		pipe(piperr);
		fd[ERR] = piperr[1];
	}
	ret = verif_line(lsttostr(tree->content), fd, fd_lst[TOCLOSE]);
	if (fd_lst[OUT])
		manage_out(pipout[0], fd_lst[OUT], fd_lst[TOCLOSE], ret);
	if (fd_lst[ERR])
		manage_out(piperr[0], fd_lst[ERR], fd_lst[TOCLOSE], ret);
	return (ret);
}


/*resoud arbre en recursif, fonction qu'on rappelle sur les noeud pour descendre
le tableau c'est les fd en entree, sortie et sortie d'erreur et les fd a fermer
fd[IN], fd[OUT], fd[ERR], fd[TOCLOSE]
se remplit dans  pipe et redirections*/
int		res(t_tree *tree, t_list *fd[4])
{
	int ret;

	if (!tree)
		return(1);
	else if (ISSEP(T(tree)->type))
		ret = exec_separation(tree, fd);
	else if (ISPIP(T(tree)->type))
		ret = exec_pipe(tree, fd);
	else if (ISRED(T(tree)->type))
		ret = exec_redirection(tree, fd);
	else
		ret = exec_command(tree, fd);
	return (ret);
}
