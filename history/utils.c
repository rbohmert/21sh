#include "../includes/21.h"

void		rewrite_history(void)
{
	t_2list *lst;
	int		fd;
	char	*file_name;

	lst = (sg_history(NULL))->lst;
	file_name = join_path(get_env(sg_env(NULL), "HOME="), HISTORY_FILE);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	}
	return (lst);
}
	
		

t_history	*get_history(void)
{
	int			fd;
	t_history	*hst;
	char		*file_name;

	if (!(hst = malloc(sizeof(t_history))))
		return (NULL);
	hst->lst = NULL;
	hst->current = NULL;
	file_name = join_path(get_env(sg_env(NULL), "HOME="), HISTORY_FILE);
	fd = open(file_name, O_RDWR | O_CREAT, 0644);
	hst->lst = get_lst_from_file(fd);
	close(fd);
	free(file_name);//certainement des fuite avec les joint
	return (hst);
}
		

t_history  *sg_history(t_history *history)
{
	static t_history *history_sav;

	if (history == NULL)
		return (history_sav);
	history_sav = history;
	return (NULL);
//		hst->fd = open(HISTORY_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
}
