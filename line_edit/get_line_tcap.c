#include "../includes/21.h"

void	init_sh(t_sh *sh)
{

	if (!init_term(sh))
		return ;
	get_sh(sh);
	sh->curs = 0;
	sh->lenline = 0;
	sh->line = malloc(1);
	sh->line[0] = 0;
	sh->yfirstl = get_curs_y();
	sh->curscc = -1;
	sh->copy = NULL;
}

void	catch_sigint(int sig)
{
	t_sh *sh;

	(void)sig;
	sh = get_sh(NULL);
	rewrite_line(sh);
	sh->curs = 0;
	sh->lenline = 0;
	free(sh->line);
	sh->line = ft_strnew(1);
	sh->curscc = -1;
	if (sh->copy)
		free(sh->copy);
	sh->copy = NULL;
	ft_putstr("\n?>");
	sh->yfirstl = get_curs_y();
}

void	change_size(int sig)
{
	t_sh *sh;

	(void)sig;
	sh = get_sh(NULL);
	ioctl(0, TIOCGWINSZ, &(sh->win));
	curs_pos(sh);
}

void	get_line_t(int fd)
{
	t_sh sh;
	char buf[10];

	signal(SIGINT, catch_sigint);
	signal(SIGWINCH, change_size);
	init_sh(&sh);
	bzero(buf, 10);
	while (read(0, buf, 10))
	{
		if (!ft_strcmp(buf, "\n"))
		{
			restore_term(&sh);
			ft_putendl_fd(sh.line, fd);
			free(sh.line);
			exit(0);
		}
		else if (ISCTRL(buf) && buf[0] == 4)
		{
			restore_term(&sh);
			sg_history(NULL, 1);
			exit(0);
		}	
		app_key(buf, &sh);
		bzero(buf, 10);
	}
}

char *fork_getline()
{
	int pip[2];
	int pid;
	char *line;

	pipe(pip);
	if ((pid = fork()) == 0)
		get_line_t(pip[1]);
	close(pip[1]);
	waitpid(pid, 0, 0);
	if (get_next_line(pip[0], &line) == 0)
		exit(0);
	close(pip[0]);
	return (line);
}	


int	ft_strcntc(char *str, char c)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

char chropenquote(char *str)
{
	while (*str)
	{
		if (*str == '"')
		{
			while (*(++str) != '"')
				if (*(str) == 0)
					return ('"');
		}
		else if (*str == '\'')
		{
			while (*(++str) != '\'')
				if (*(str) == 0)
					return ('\'');
		}
		str++;
	}
	return (0);
}

void	change_history(char *str, t_history *hst)
{
	is_empty_line(str) ? 0 : history_add(str);
	hst->current = NULL;
	if (!is_empty_line(str))
	{
		free(((t_elemhst *)(hst->lst->content))->line);
		((t_elemhst *)(hst->lst->content))->line = ft_strdup(str);
	}
	if (is_empty_line(((t_elemhst *)(hst->lst->content))->line))
	{
		free(((t_elemhst *)(hst->lst->content))->line);
		free(hst->lst->content);
		hst->lst = hst->lst->next;
		free(hst->lst->prev);
		hst->lst->prev = NULL;
	}
	rewrite_history();

}
char *get_line_tcap(void)
{
	char *line;
	char *next;
	char *tmp;
	char c;
	t_history *hst;

	(!(hst = get_history())) ? sg_history(NULL, 1) : sg_history(hst, 0);
	line = fork_getline();
	sg_history(NULL, 1);
	while ((c = chropenquote(line))) //(ft_strcntc(line , '"') % 2) != 0)
	{
		ft_putchar(c);
		ft_putchar('>');
		next = ft_strjoin(line, "\n");
		free(line);
		line = next;
		tmp = line;
		next = fork_getline();
		line = ft_strjoin(line, next);
		free(tmp);
		free(next);
	}
	if ((hst = get_history()))
		sg_history(hst, 0);	
	if (hst)
		change_history(line, hst); 
	return (line);
}
/*int main(int ac , char **av, char **env)
  {
  char *line;

  ft_putstr("?>");
  line = NULL;
  get_env(env);
  block_sig();
  while (get_line_cap())
  {
  ft_putstr("?>");
  }
  }*/
