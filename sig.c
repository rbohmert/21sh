#include "includes/21.h"

void	exit_pipe(int sig)
{
	ft_putendl("hfudi");
	(void)sig;
	exit(0);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)// || sig == SIGQUIT)// || sig == SIGTERM)
	{
		while (wait(0) > 0)
			;
		ft_putchar_fd('\n', 1);
		//restore_term(get_sh(NULL));
		//exit(0)	;
	}	
	//else if (sig == SIGPIPE)
	//	kill(0, SIGINT);
	//	ft_putendl("hnvdihi");
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
	int sig[2] = {SIGINT, SIGCHLD};
	int i;

	i = 0;
	while (i < 2)
		signal(sig[i++], sighandler);
}

