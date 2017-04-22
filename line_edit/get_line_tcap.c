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

char *get_line_tcap(void)
{
	t_sh sh;
	char buf[10];

	init_sh(&sh);
	bzero(buf, 10);
	while (read(0, buf, 10))
	{
		if (!strcmp(buf, "\n"))
		{
			restore_term(&sh);
			history_add(sh.line);
			(sg_history(NULL))->current = NULL;
			rewrite_history();
			return(sh.line);
		}
		app_key(buf, &sh);
		bzero(buf, 10);
	}
	return (NULL);
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
