#include "../includes/21.h"
#define E(x) ((t_elemhst *)(x->content))

int		is_empty_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\v')
			return (0);
		str++;
	}
	return (1);
}

void	history_up(t_sh *sh)
{
	t_history *hst;

	hst = sg_history(NULL, 0);
	if (!hst || !hst->lst || (hst->current && !hst->current->next))
		return;
	if (!hst->current)
	{
		history_add(sh->line);
		hst->current = hst->lst->next;
	}
	else
	{
		if (ft_strcmp(E(hst->current)->line, sh->line))
			history_add(sh->line);
		hst->current = hst->current->next;
	}
	free(sh->line);
	sh->line = ft_strdup(E(hst->current)->line);
	sh->lenline = ft_strlen(sh->line);
	rewrite_line(sh);
	sh->curs = sh->lenline;
}

void	history_down(t_sh *sh)
{
	t_history *hst;

	hst = sg_history(NULL, 0);
	if (!hst || !hst->lst || !hst->current || (hst->current && !hst->current->prev))
		return;
	if (ft_strcmp(((t_elemhst *)(hst->current->content))->line, sh->line))
		history_add(sh->line);
	hst->current = hst->current->prev;
	free(sh->line);
	sh->line = ft_strdup(E(hst->current)->line);
	sh->lenline = ft_strlen(sh->line);
	rewrite_line(sh);//reecrire ca	
	sh->curs = sh->lenline;
}

void	history_add(char *str)
{
	t_history *hst;
	t_elemhst *elem;

	if ((hst = sg_history(NULL, 0)) == NULL)
		return;
	if (hst->current)
	{
		free(E(hst->current)->line);
		E(hst->current)->line = ft_strdup(str);
	}
	else
	{
		if (!(elem = malloc(sizeof(t_elemhst))))
			return ;
		elem->line = ft_strdup(str);	
		elem->no = hst->lst ? E(hst->lst)->no + 1 : 0;
		ft_push_2front(&hst->lst, elem);
	}
}
