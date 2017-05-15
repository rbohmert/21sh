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

char *get_line_tcap(void)
{
	t_sh sh;
	char buf[10];
	int pip[2];
	int pid;
	char *line;

	pipe(pip);
	if ((pid = fork()) == 0)
	{
		sg_history(get_history());
		signal(SIGINT, catch_sigint);
		signal(SIGWINCH, change_size);
		init_sh(&sh);
		bzero(buf, 10);
		while (read(0, buf, 10))
		{
			if (!ft_strcmp(buf, "\n"))
			{	
				restore_term(&sh);
				history_add(sh.line);
				(sg_history(NULL))->current = NULL;
				rewrite_history();
				ft_putendl_fd(sh.line, pip[1]);
				exit(0);
				//return(sh.line);
			}
			else if (ISCTRL(buf) && buf[0] == 4)
			{
				restore_term(&sh);
				sg_history((t_history *)1);
				exit(0);
			}	
			app_key(buf, &sh);
			bzero(buf, 10);
		}
	}
	close(pip[1]);
	waitpid(pid, 0, 0);
	if (get_next_line(pip[0], &line) == 0)
		exit(0);
	close(pip[0]);
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
