#include "../includes/21.h"

void		rewrite_history(void)
{
	t_2list *lst;
	int		fd;
	char	*file_name;

	lst = (sg_history(NULL, 0))->lst;
	file_name = join_path(get_env(sg_env(NULL), "HOME="), HISTORY_FILE);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(file_name);
	while (lst->next)
		lst = lst->next;
	while (lst)
	{
		ft_putstr_fd(E(lst)->line, fd);
		ft_putchar_fd('\n', fd);
		lst = lst->prev;
	}	
}

t_2list		*get_lst_from_file(int fd)
{
	char *line;
	t_elemhst *elem;
	int i;
	t_2list *lst;
	
	line = NULL;
	i = 0;
	lst = NULL;
	while (get_next_line(fd, &line))
	{	
		if (!(elem = malloc(sizeof(t_elemhst))))
			return (NULL);
		elem->line = ft_strdup(line);
		elem->no = i++;
		ft_push_2front(&lst, elem);
		free(line);
	}
	free(line);
	return (lst);
}

t_history	*get_history(void)
{
	int			fd;
	t_history	*hst;
	char		*file_name;
	char		*home;

	home = get_env(sg_env(NULL), "HOME=");
	file_name = home ? join_path(home, HISTORY_FILE) : NULL;
	if ((fd = open(file_name, O_RDWR | O_CREAT, 0644)) == -1 || !home)
		return (NULL);
	if (!(hst = malloc(sizeof(t_history))))
		return (NULL);
	file_name ? free(file_name) : 0;
	hst->lst = NULL;
	hst->current = NULL;
	hst->lst = get_lst_from_file(fd);
	close(fd);
	return (hst);
}

void		free_history(t_history *hst)
{
	t_2list *lst;

	if (hst == NULL)
		return ;
	while (hst->lst)
	{
		lst = hst->lst;
		hst->lst = hst->lst->next;
		free(((t_elemhst *)(lst->content))->line);
		free(lst->content);
		free(lst);
	}
	free(hst);
}

t_history  *sg_history(t_history *history, int nohistory)
{
	static t_history *history_sav = NULL;

	if (nohistory)
	{
		free_history(history_sav);
		history_sav = NULL;
		return (NULL);
	}
	if (history == NULL)
		return (history_sav);
	if (history_sav != NULL)
		free_history(history_sav);
	history_sav = history;
	return (NULL);
//		hst->fd = open(HISTORY_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
}

void	history_print(char **arg)
{
	t_history	*hst;
	t_2list		*lst;


	if (arg[1])
	{
		ft_putstr_fd("Usage: history", 2);
		return ;
	}
	hst = get_history();
	lst = hst->lst;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		while (lst)
		{
			ft_putnbr(((t_elemhst *)(lst->content))->no);
			ft_putstr("  ");
			ft_putendl(((t_elemhst *)(lst->content))->line);
			lst = lst->prev;
		}
	}
	free_history(hst);
}

