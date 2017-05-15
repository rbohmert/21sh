/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 23:37:35 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/27 05:47:24 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/21.h"


/* transforme liste de char en liste item avec un char * et un type:
mot, separateur, pipe, redirection, redirection de fd (agregation)*/
void	typage(t_list *lst)
{
	char	*tok;
	t_item	*item;

	while (lst != NULL)
	{
		tok = lst->content;
		if (lst->content && lst->content_size == 1)
		{
			if (*tok == '&' || *tok == ';' || !ft_strcmp(tok, "||"))
				lst->content_size |= SEP;
			else if (*tok == '|')
				lst->content_size |= PIP;
			else if (tok[1] == '>' || *tok == '<')
			{
				lst->content_size |= RED;
				if (tok[2] == '&')
					lst->content_size |= RFD;
			}
		}
		item = malloc(sizeof(t_item));
		item->itm = lst->content;
		item->type = lst->content_size;
		lst->content = item;
		lst = lst->next;
	}
}

char	*redir(char *line, int i, int *adrr_cmp, char *tok)
{
	tok[0] = (i > 0 && line[i - 1] == '2') ? '2' : '1'; 
	tok[1] = '>';
	if (line[i + 1] == '&')
	{
		tok[2] = '&';
		if (line[i + 2] && (line[i + 2] == '1' || line[i + 2] == '2'))
			tok[3] = line[i + 2];
		//else parse error
		tok[4] = 0;
		*adrr_cmp += 3;
	}
	else if (line[i + 1] == '>')
	{
		tok[2] = '>';
		if (line[i + 2] && line[i + 2] == '&')
			ft_putstr("parse error");
		ft_strcpy(tok + 3, "\0\0");
		*adrr_cmp += 2;
	}
	else
	{
		ft_strcpy(tok + 2, "\0\0\0");
		(*adrr_cmp)++;
	}
	return (tok);
}

//recupere le token et avance le compteur après
char	*gettok(char *line, int i, int *adrr_cmp)
{
	char *tok;
	char c;

	c = line[i];
	if ((tok = (char *)malloc(5)) == NULL)
		return (NULL);
	if (c == '<' || c == '|' || c == '&')
	{
		tok[0] = c;
		tok[1] = (line[i + 1] == c ? c : 0);
		ft_strcpy(tok + 2, "\0\0\0");
		*adrr_cmp += (line[i + 1] == c) ? 2 : 1;
	}
	if (c == ';')
	{
		tok = ft_strdup(";");
		(*adrr_cmp)++;
	}
	if (c == '>')
		redir(line, i, adrr_cmp, tok);//recupère token chiant redirection sortie
	if (c == 0)
		tok = NULL;//free leaks
	return (tok);
}


void	split_text(char *str, t_list **lst)
{
	char **strtab;
	int i;

	i = 0;
	strtab = ft_strsplit(str, ' ');
	free(str);
	while (strtab[i])
		ft_push_back(lst, ft_strdup(strtab[i++]), 0);
	ft_freestrtab(strtab);
}

/*transforme la str recu en list; avance jusqua trouver un '<>|&',
 push tout ce qui est avant donc des "mots" avec 1 mot par maillon,
 puis push le maillon  'token' donc un truc de commande '2>&1' '&&' ...ect
pour les noms token ect et dans les define j'ai du faire nimp, pas grave*/

t_list	*lexer(char *line)
{
	int i;
	int tmp;
	int len;
	t_list *lst;

	lst = NULL;
	i = 0;
	tmp = 0;
	while (1)
	{
		if (CISSYM(line[i]) || !line[i])
		{
			//len = taille de la str depuis le dernier token
			len = i - tmp - ((line[i] == '>' && (i > 0 && (line[i - 1] == '2' || line[i - 1] == '1'))) ? 1 : 0);//ternaire pour enlever 1 a len si le token c'est '2>&1' ou '1>' pas compter le chiffre avant les symboles
			split_text(ft_strsub(line, tmp, len), &lst);// push les mot
			if (line[i])
				ft_push_back(&lst, gettok(line, i, &i), 1); //push le token et avance i apres le token
			tmp = i;
			if (!line[i])
				break;
		}
		else
			i++;
	}
	typage(lst);// type la list pour le parsing
	//free(line);
	return (lst);
}
