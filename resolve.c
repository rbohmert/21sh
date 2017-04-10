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

#include "21.h"

int		exec_separation(t_tree *tree, t_list *in, t_list *out)
{
	int ret;

	if (!ft_strcmp(T(tree)->itm, ";"))
	{
		res(tree->lf, in, out);
		res(tree->rg, in, out);
		ret = 1;
	}
	if (!ft_strcmp(T(tree)->itm, "&&"))
	{
		if (ret = res(tree->lf, in, out))
			ret = res(tree->rg, in, out);
	}
	if (!ft_strcmp(T(tree)->itm, "||"))
	{
		if (!(ret = res(tree->lf, in, out)))
			ret = res(tree->rg, in, out);
	}
	if (!ft_strcmp(T(tree)->itm, "&"))
	{
		ft_putendl("CEEEEEEEEEEEEECIIIIIIIIIII EEEESSSTTT EEEENNN BBBAACCCKKKGGRRROOOOOUUUUNNNDDDD");
		if (res(tree->lf, in, out))
			ret = res(tree->rg, in, out);
	}
	return (ret);	
}

int exec_pipe(t_tree *tree, t_list *in, t_list *out)
{	
	int		pip[2];
	int 	ret;

	ret = 0;
	if (pipe(pip) == -1)
		ft_putstr("pipeeerrroror");
	ft_push_back(&out, &pip[1], 0);
	ret = res(tree->lf, in, out);
	del(&in);
	del(&out);
	close(pip[1]);
	ft_push_back(&in, &pip[0], 0);
	ret = res(tree->rg, in, out);
	//del(&in); faut trouver moyen de free la derniere liste in, ce dell fais bug car psse plusieur fois en remontant l'arbre
	close(pip[0]);
	return (1);
}

int		exec_command(t_tree *tree, t_list *in, t_list *out)
{
	char *str;
	int intocom;
	int ret;
	int pip[2];

	str = lsttostr(tree->content);
	if (out && in)
	{
		intocom = manage_in(in);
		pipe(pip);
		ret = verif_line(str, sg_env(NULL), intocom, pip[1]);
		manage_out(pip[0], out);
	}
	else if (out && !in)
	{
		pipe(pip);
		ret = verif_line(str, sg_env(NULL), STDIN_FILENO, pip[1]);
		manage_out(pip[0], out);
	}
	else if (!out && in)
	{
		intocom = manage_in(in);
		ret = verif_line(str, sg_env(NULL), intocom, STDOUT_FILENO);
	}
	else 
		ret = verif_line(str, sg_env(NULL), STDIN_FILENO, STDOUT_FILENO);
	return (ret);
}

int		res(t_tree *tree, t_list *in, t_list *out)
{
	int ret;

	if (!tree)
		return(1);
	else if (ISSEP(T(tree)->type))
		ret = exec_separation(tree, in, out);
	else if (ISPIP(T(tree)->type))
		ret = exec_pipe(tree, in, out);
	else if (ISRED(T(tree)->type))
		ret = exec_redirection(tree, in, out);
	else
		ret = exec_command(tree, in, out);
	return (ret);
}
