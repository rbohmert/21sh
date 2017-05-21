#include "../includes/21.h"

int		restore_term(t_sh *sh)
{
	sh->curs = sh->lenline;
	curs_pos(sh);
	ft_putchar('\n');
	if (tcsetattr(0, 0, &sh->tsav) == -1)
		return (0);
	return (1);
}

int		init_term(t_sh *sh)
{
	char *name_term;

	name_term = get_env(sg_env(NULL), "TERM=");
	if (tgetent(NULL, name_term ? name_term : "xterm") == -1)
	{
		ft_putstr("tgetent failed");
		return (0);
	}
	if (tcgetattr(0, &sh->term) == -1 || tcgetattr(0, &sh->tsav) == -1)
		return (0);
	sh->term.c_lflag &= ~(ICANON);
	sh->term.c_lflag &= ~(ECHO);
	sh->term.c_cc[VMIN] = 1;
	sh->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &sh->term) == -1)
		return (0);
	ioctl(0, TIOCGWINSZ, &(sh->win));
	return (1);
}
