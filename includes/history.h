#ifndef HISTORY_H
# define HISTORY_H

# define HISTORY_FILE ".21sh_history"
# define E(x) ((t_elemhst *)(x->content))


typedef	struct	s_history
{
	t_2list		*current;
	t_2list		*lst;
}				t_history;

typedef struct	s_elemhst
{
	char	*line;
	int		no;
}				t_elemhst;

t_history	*get_history(void);
t_history	*sg_history(t_history *history);
void		history_up(t_sh *sh);
void		history_down(t_sh *sh);
void		history_add(char *str);
void		rewrite_history(void);

#endif
