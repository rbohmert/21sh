#include "includes/21.h"

void	sighandler(int sig)
{
	//if (sig == SIGWINCH)
	//	change_size();
	if (sig == SIGINT)// || sig == SIGQUIT)// || sig == SIGTERM)
	{
		while (wait(0) > 0)
			;
		ft_putchar_fd('\n', 1);
		//restore_term(get_sh(NULL));
		//exit(0)	;
	}	
	//else if (sig == SIGTSTP)
	//	stop(SIGTSTP);
	//else if (sig == SIGCONT)
	//	continu(SIGCONT);
	else if (sig == SIGCHLD)
		;
	else
	{
		ft_putnbr(sig);
		ft_putnbr(SIGUSR2);
		ft_putstr("signal non gere magueul\n");
	}
}

void	block_sig(void)
{
	int i;

	i = 0;
	while (i < 33)
		signal(i++, sighandler);
}

